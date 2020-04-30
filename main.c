#include "stdafx.h"
#include "utils.h"
#include "log.h"
#include "config.h"
#include "game.h"


u8 setup_boardsize()
{
	u8 ret = 0;
	while (ret < BOARD_MIN_SIZE || ret > BOARD_MAX_SIZE)
	{
		ret = read_u8("Choose the board size: ");
		if (ret < BOARD_MIN_SIZE || ret > BOARD_MAX_SIZE)
		{
			printf("Invalid size (%hhux%hhu), a board must be between %hhux%hhu and %hhux%hhu\n",
						 ret, ret, BOARD_MIN_SIZE, BOARD_MIN_SIZE, BOARD_MAX_SIZE, BOARD_MAX_SIZE);
		}
	}
	return ret;
}

u8* setup_boatamounts(u8 boardsz)
{
	char prompt[38];
	u8   max_boats = boardsz * boardsz / 25;
	u8*  boats     = (u8*) malloc((TYPE_TSHAPE_5 + 1) * sizeof(u8));
	boats[0]       = 0;

	while (boats[0] == 0)
	{
		u16 all = 0;

		for (u8 i = 1; i <= TYPE_TSHAPE_5; i++)
		{
			sprintf(prompt, "Choose the amount of type %hhu boats: ", i);
			boats[i] = read_u8(prompt);
			while (boats[i] == 0)
			{
				printf("You must have at least one boat of each type in your game\n");
				boats[i] = read_u8(prompt);
			}
			all += boats[i];
		}

		boats[0] = all;

		// Overflow detected (u16 vs u8), user past the 255 limit or above max_boats limit
		if (boats[0] != all || boats[0] > max_boats)
		{
			printf("You can't have more than %hhu boats on your game\n", max_boats);
			boats[0] = 0;
		}
	}
	return boats;
}

void read_boat(Board* board, BoatType type, u8 remaining, u8 total, bool mode)
{
	Boat* boat  = boat_construct(type, 0);
	bool rotate = false;
	s16 x       = -1;
	s16 y       = -1;

	// Rotation
	if (type != TYPE_LINEAR_1)
	{
		while (true)
		{
			if (mode)
			{
				// Manual rotation
				boat_print(boat);
				rotate = read_bool("Would you like to rotate your boat? (0 = no, 1 = yes)\n");
			}
			else
			{
				// Random rotation
				rotate = rand() % 2 == 1;
			}

			if (!rotate)
			{
				break;
			}

			boat_rotate(boat);
		}
	}

	// Coordinates
	while (x < 0 || y < 0 || x >= board->height || y >= board->width)
	{
		if (mode)
		{
			// Manual coordinates
			printf("Choose the coordinates for your boat\n");
			printf("Note: You must input the coordinates for the CENTER coordinate of the 5x5 boat matrix\n\n");
			x = read_u8("Vertical coordinate: ");
			y = read_u8("Horizontal coordinate: ");
		}
		else
		{
			// Random coordinates
			x = rand() % (board->height - 1);
			y = rand() % (board->width  - 1);
		}

		if (board_add(board, boat, x-2, y-2) != RETURN_OK)
		{
			if (mode)
			{
				printf("It's not possible to add the boat matrix on (%hu, %hu) to (%hu, %hu)\n", x-2, y-2, x+2, y+2);
			}
			x = -1;
			y = -1;
		}
	}
}

void setup_board(u8 player, Board* board, u8* boat_count)
{
	clear();
	printf("Player %hhu, it's time to set up your board\n", player);
	bool config = read_bool("Choose the configuration type (0 = random, 1 = manual): ");

	for (u8 type = TYPE_TSHAPE_5; type >= 1; type--)
	{
		for (u8 remaining = boat_count[type]; remaining > 0; remaining--)
		{
			if (config)
			{
				newline();
				board_print(board, false);
				newline();
			}
			read_boat(board, type, remaining, boat_count[type], config);
		}
	}
}

return_code player_move(Game* game, u8 player)
{
	Board*      board;
	return_code code;
	s16         x;
	s16         y;
	bool        print;

	switch (player)
	{
		case 1:
			board = game->board_p1;
			break;
		case 2:
			board = game->board_p2;
			break;
		default:
			_logf(L_FATAL, "Tried running player_move with player %hhu", player);
			return false;
	}

	print = false;

	clear();
	printf("Player %hhu, it's your turn!\n", player);

	newline();
	print = read_bool("Do you want to print your own board (0 = no, 1 = yes): ");
	if (print)
	{
		newline();
		printf("Your board: \n");
		board_print(player == 1 ? game->board_p1 : game->board_p2, false);
	}
	print = false;

	newline();
	printf("Opponent's board: \n");
	board_print(board, true);

	newline();
	printf("Choose where you want to strike on your opponents' board: \n");

	code = RETURN_OK;

	while (code != GAME_ATTACK_HIT_SEA && code != GAME_ATTACK_HIT_BOAT)
	{
		x = read_u8("Vertical coordinate: ");
		y = read_u8("Horizontal coordinate: ");

		code = game_attack(game, player, x, y);

		switch (code)
		{
			case GAME_INVALID_GAME:
			case GAME_INVALID_PLAYER:
				_logf(L_FATAL, "Internal error: invalid argument on player_move (0x%X)", code);
				break;
			case GAME_INVALID_COORDINATES:
				printf("Invalid coordinates, the board is not that big!\n");
				break;
			case GAME_ATTACK_ALREADY_HIT:
				printf("You already shot there previously!\n");
				break;
			case GAME_ATTACK_HIT_SEA:
				printf("You hit the sea...\n");
				break;
			case GAME_ATTACK_HIT_BOAT:
				printf("You hit something!\n");
				break;
			default:
				_logf(L_FATAL, "Internal error: unhandled error code on player_move (0x%X)", code);
		}
	}

	return code;
}

void settings()
{
	u8 menu;
	menu = 0;

	while (true)
	{
		clear();
		printf("Current settings:\n");
		newline();
		printf("LOGGING = %s\n"         , LOGGING       ? "true" : "false");
		printf("CLEAR_SCREEN = %s\n"    , CLEAR_SCREEN  ? "true" : "false");
		printf("REPLAY_ON_HIT = %s\n"   , REPLAY_ON_HIT ? "true" : "false");
		newline();
		printf("1) Toggle LOGGING\n");
		printf("2) Toggle CLEAR_SCREEN\n");
		printf("3) Toggle REPLAY_ON_HIT\n");
		printf("9) Return to Main Menu\n");
		newline();
		menu = read_u8("Choose a number: ");

		switch (menu)
		{
			case 1:
				LOGGING = !LOGGING;
				break;
			case 2:
				CLEAR_SCREEN = !CLEAR_SCREEN;
				break;
			case 3:
				REPLAY_ON_HIT = !REPLAY_ON_HIT;
				break;
			case 9:
				return;
			default:
				printf("Invalid number\n");
		}
	}
}

void menu()
{
	u8 menu;
	menu = 0;

	// Menu
	while (menu != 1)
	{
		clear();
		printf("Welcome to Kancolle Game!\n");
		newline();
		printf("1) New Game\n");
		printf("2) Settings\n");
		printf("3) Exit Game\n");
		newline();
		menu = read_u8("Choose a number: ");

		// Settings
		if (menu == 2)
		{
			settings();
		}
		// Exit Game
		if (menu == 3)
		{
			exit(0);
		}
	}
}

int main(int argc, char *argv[])
{
	// Define seed for randomization
	srand(time(NULL));

	// Game menu
	menu();

	// Game initial setup: config, board size, boat amount
	u8    boardsz = setup_boardsize();
	u8*   boats   = setup_boatamounts(boardsz);
	Game* game    = game_construct(boardsz, boardsz);

	// Setup both players' boards
	setup_board(1, game->board_p1, boats);
	setup_board(2, game->board_p2, boats);

	// Gameplay
	for (u8 player = 1; player <= 2 && game->state == 0; player++)
	{
		// Player gets to play again on successful hit if the setting is enabled
		if (player_move(game, player) == GAME_ATTACK_HIT_BOAT && REPLAY_ON_HIT)
		{
			player--;
		}
		if (player == 2)
		{
			player = 0;
		}
	}

	// Announce player who won
	printf("Player %hhu has won\n", game->state);

	// Destruct objects and gracefully terminate
	free(boats);
	game_destruct(game);
	return 0;
}
