#include "game.h"


Game* game_construct(u8 height, u8 width)
{
	Game* ret;

	ret           = malloc(sizeof(Game));
	ret->state    = 0;
	ret->board_p1 = board_construct(height, width);
	ret->board_p2 = board_construct(height, width);

	if (ret->board_p1 == NULL || ret->board_p2 == NULL)
	{
		_logf(L_FATAL, "Board creation failed, cannot initialize game");
		return NULL;
	}

	_logf(L_INFO, "Game created");
	return ret;
}

return_code game_destruct(Game* game)
{
	if (game == NULL)
	{
		return GAME_INVALID_GAME;
	}

	board_destruct(game->board_p1);
	board_destruct(game->board_p2);

	_logf(L_INFO, "Game with state %hhu destructed", game->state);
	free(game);

	return RETURN_OK;
}

return_code game_print(Game* game)
{
	if (game == NULL)
	{
		return GAME_INVALID_GAME;
	}

	printf("State: %hhu\n", game->state);

	return RETURN_OK;
}

return_code game_attack(Game* game, u8 player, u8 x, u8 y)
{
	Board* board;

	if (game == NULL)
	{
		return GAME_INVALID_GAME;
	}

	if (player != 1 && player != 2)
	{
		return GAME_INVALID_PLAYER;
	}

	board = (player == 1) ? game->board_p1 : game->board_p2;

	if (x >= board->height || y >= board->width)
	{
		return GAME_INVALID_COORDINATES;
	}

	if (board->matrix[x * board->height + y].shot != 0)
	{
		return GAME_ATTACK_ALREADY_HIT;
	}

	if (board->matrix[x * board->height + y].boat == 0x0)
	{
		board->matrix[x * board->height + y].shot = 1;
		return GAME_ATTACK_HIT_SEA;
	}
	else
	{
		board->matrix[x * board->height + y].shot = 2;
		board->matrix[x * board->height + y].boat->life--;
		game_verify(game, player);
		return GAME_ATTACK_HIT_BOAT;
	}
}

return_code game_verify(Game* game, u8 player)
{
	Board* board;

	if (game == NULL)
	{
		return GAME_INVALID_GAME;
	}

	if (player != 1 && player != 2)
	{
		return GAME_INVALID_PLAYER;
	}

	board = (player == 1) ? game->board_p1 : game->board_p2;

	for (u8 x = 0; x < board->height; x++)
	{
		for (u8 y = 0; y < board->width; y++)
		{
			// Game still not over (found Boat Cell without hit)
			if (board->matrix[x * board->height + y].boat != 0x0 && board->matrix[x * board->height + y].shot == 0)
			{
				_logf(L_INFO, "verify_state: Found %hhu at %hhu, %hhu", board->matrix[x * board->height + y].shot, x, y);
				game->state = false;
				return RETURN_OK;
			}
		}
	}
	// Game over
	game->state = true;
	return RETURN_OK;
}
