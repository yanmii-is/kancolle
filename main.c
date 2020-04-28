#include "stdafx.h"
#include "boat.h"
#include "game.h"
#include "utils.h"
#include "config.h"


u8 setup_boardsize()
{
  u8 ret = 0;
  while (ret < BOARD_MIN_SIZE || ret > BOARD_MAX_SIZE)
  {
    ret = read_u8("Choose the board size: ");
    if (ret < BOARD_MIN_SIZE || ret > BOARD_MAX_SIZE)
    {
      printf("Invalid size (%hhux%hhu), a board must be between %hhux%hhu and %hhux%hhu\n", ret, ret, BOARD_MIN_SIZE, BOARD_MIN_SIZE, BOARD_MAX_SIZE, BOARD_MAX_SIZE);
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
  Boat* boat            = boat_construct(type, 0);
  BoatRotation rotation = 0;
  bool rotate           = false;
  s16 x                 = -1;
  s16 y                 = -1;

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
      printf("Note: You must input the coordinates for the UPMOST LEFT coordinate of the 5x5 boat matrix\n\n");
      x = read_u8("Vertical coordinate: ");
      y = read_u8("Horizontal coordinate: ");
    }
    else
    {
      // Random coordinates
      x = rand() % (board->height - 1);
      y = rand() % (board->width  - 1);
    }

    if (!board_add(board, boat, x, y))
    {
      if (mode)
      {
        printf("It's not possible to add the boat matrix on (%hu, %hu) to (%hu, %hu)\n", x, y, x + 4, y + 4);
      }
      x = -1;
      y = -1;
    }
  }
}

void setup_board(u8 player, Board* board, u8* boat_count, bool mode)
{
  clear();
  printf("Player %hhu, it's time to set up your board\n", player);

  for (u8 type = TYPE_TSHAPE_5; type >= 1; type--)
  {
    for (u8 remaining = boat_count[type]; remaining > 0; remaining--)
    {
      newline();
      board_print(board, false);
      newline();
      read_boat(board, type, remaining, boat_count[type], mode);
    }
  }
}

bool player_move(Game* game, u8 player)
{
  Board* board;
  u8     x;
  u8     y;

  switch (player)
  {
    case 1:
      board = game->board_p1;
    case 2:
      board = game->board_p2;
    default:
      _logf(L_FATAL, "Tried running player_move with player %hhu", player);
      return false;
  }

  clear();
  printf("Player %hhu, it's your turn!\n", player);
  newline();
  board_print(board, true);
  newline();
  printf("Choose where you want to strike on your opponents' board: \n");

  while (true)
  {
    x = read_u8("Vertical coordinate: ");
    y = read_u8("Horizontal coordinate: ");

    // Check whether the given coordinates are outside of the board
    if (x >= board->height || y >= board->width)
    {
      printf("Invalid coordinates, the board is not that big!\n");
      continue;
    }
    else if (board->matrix[x * board->height + y].shot != 0)
    {
      printf("You already shot there previously!\n");
      continue;
    }

    break;
  }

  return board_attack(board, x, y);
}


int main(int argc, char *argv[])
{
  // Define seed for randomization
  srand(time(NULL));

  // Clear the user's screen
  clear();

  // Game initial setup: config, board size, boat amount
  bool  config  = read_bool("Choose the configuration type (0 = random, 1 = manual): ");
  u8    boardsz = setup_boardsize();
  u8*   boats   = setup_boatamounts(boardsz);
  Game* game    = game_construct(boardsz, boardsz);

  // Setup both players' boards
  setup_board(1, game->board_p1, boats, config);
  setup_board(2, game->board_p2, boats, config);

  // Gameplay
  bool hit = false;
  while (game->state == 0)
  {
    for (int player = 1; player <= 2; player++)
    {
      hit = player_move(game, player);
      game_verify(game, player);
      if (game->state != 0)
      {
        printf("Player %hhu has won\n", game->state);
        break;
      }
      // Player gets to play again on successful hit if the setting is enabled
      if (hit && REPLAY_ON_HIT)
      {
        player--;
      }
      hit = false;
    }
  }

  // Destruct objects and gracefully terminate
  game_destruct(game);
  return 0;
}
