#include "boat.h"
#include "game.h"
#include "utils.h"
#include "config.h"


uint8_t setup_boardsize()
{
  uint8_t ret = 0;
  while (ret < BOARD_MIN_SIZE || ret > BOARD_MAX_SIZE)
  {
    ret = read_u8("Choose the board size: ");
    if (ret < BOARD_MIN_SIZE || ret > BOARD_MAX_SIZE)
    {
      printf("Invalid size (%dx%d), a board must be between %dx%d and %dx%d\n", ret, ret, BOARD_MIN_SIZE, BOARD_MIN_SIZE, BOARD_MAX_SIZE, BOARD_MAX_SIZE);
    }
  }
  return ret;
}

uint8_t* setup_boatamounts(uint8_t boardsz)
{
  char     prompt[38];
  uint8_t  max_boats = boardsz * boardsz / 25;
  uint8_t* boats     = (uint8_t*) malloc((TYPE_TSHAPE_5 + 1) * sizeof(uint8_t));
  boats[0]           = 0;

  while (boats[0] == 0)
  {
    uint16_t all = 0;

    for (uint8_t i = 1; i <= TYPE_TSHAPE_5; i++)
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
      printf("You can't have more than %d boats on your game\n", max_boats);
      boats[0] = 0;
    }
  }
  return boats;
}

Boat* read_boat(Board* board, BoatType type, uint8_t remaining, uint8_t total, bool mode)
{
  Boat* ret             = construct_boat(type, 0);
  BoatRotation rotation = 0;
  bool rotate           = true;
  int16_t x             = -1;
  int16_t y             = -1;

  // Manual rotation
  if (mode && type != TYPE_LINEAR_1)
  {
    while (rotate)
    {
      // Print default bitmap
      print_bitmap(ret);
      rotate = read_bool("Would you like to rotate your boat? (0 = no, 1 = yes)\n");

      if (!rotate)
      {
        break;
      }

      rotate_boat(ret);
    }
  }
  // Random rotation
  else
  {
    while (rand() % 2 == 1)
    {
      rotate_boat(ret);
    }
  }

  // Coordinates
  while (x < 0 || y < 0 || x >= board->height || y >= board->width)
  {
    if (mode)
    {
      printf("Choose the coordinates for your boat\n");
      printf("Note: You must input the coordinates for the UPMOST LEFT coordinate of the 5x5 boat matrix\n\n");
      x = read_u8("Vertical coordinate: ");
      y = read_u8("Horizontal coordinate: ");
    }
    else
    {
      x = rand() % (board->height - 1);
      y = rand() % (board->width  - 1);
    }

    // Add boat
    if (!add_boat(board, ret, x, y))
    {
      if (mode)
      {
        printf("It's not possible to add the boat matrix on (%hu, %hu) to (%hu, %hu)\n", x, y, x+5, y+5);
      }
      x = -1;
      y = -1;
    }
  }

  return ret;
}

void setup_board(uint8_t player, Board* board, uint8_t* boat_count, bool mode)
{
  clear();
  printf("Player %hhu, it's time to set up your board\n", player);

  for (uint8_t type = TYPE_TSHAPE_5; type >= 1; type--)
  {
    for (uint8_t remaining = boat_count[type]; remaining > 0; remaining--)
    {
      newline();
      print_board(board, false);
      newline();
      Boat* boat = read_boat(board, type, remaining, boat_count[type], mode);
    }
  }
}

void player_move(uint8_t player, Game* game)
{
  Board* board;
  uint8_t x, y;

  if (player == 1)
  {
    board = game->board_p2;
  }
  else if (player == 2)
  {
    board = game->board_p1;
  }
  else
  {
    _logf(L_FATAL, "Tried running player_move with player %hhu", player);
    return;
  }

  clear();
  printf("Player %hhu, it's your turn!\n", player);
  newline();
  print_board(board, true);
  newline();\
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

  if (verify_state(board))
  {
    game->state = true;
  }

  if (board->matrix[x * board->height + y].boat == 0x0)
  {
    printf("You hit the sea...\n");
    board->matrix[x * board->height + y].shot = 1;
  }
  else
  {
    printf("You hit something!\n");
    board->matrix[x * board->height + y].shot = 2;
    board->matrix[x * board->height + y].boat.damage++;

    // Player gets to play again on successful hit if the setting is enabled
    if (REPLAY_ON_HIT && !game->state)
    {
      player_move(player, game);
    }
  }

  return;
}


int main(int argc, char *argv[])
{
  // Define seed for randomization
  srand(time(NULL));

  // Clear the user's screen
  clear();

  // Game initial setup: config, board size, boat amount
  bool     config  = read_bool("Choose the configuration type (0 = random, 1 = manual): ");
  uint8_t  boardsz = setup_boardsize();
  uint8_t* boats   = setup_boatamounts(boardsz);
  Game*    game    = construct_game(boardsz, boardsz);

  // Setup both players' boards
  setup_board(1, game->board_p1, boats, config);
  setup_board(2, game->board_p2, boats, config);

  // Gameplay
  while (!game->state)
  {
    player_move(1, game);
    if (game->state)
    {
      printf("Player 1 has won\n");
      break;
    }
    player_move(2, game);
    if (game->state)
    {
      printf("Player 2 has won\n");
      break;
    }
  }

  // Destruct objects and gracefully terminate
  destruct_game(game);
  return 0;
}
