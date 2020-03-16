#include "game.h"
#include "utils.h"
#include "config.h"


uint8_t read_boardsize()
{
  uint8_t ret = 0;
  while (ret < 5 || ret > 100)
  {
    ret = read_u8("Choose the board size: ");
    if (ret < 5 || ret > 100)
    {
      printf("Invalid size (%dx%d), a board must be between 5x5 and 100x100\n", ret, ret);
    }
  }
  return ret;
}

uint8_t read_amount(uint8_t size)
{
  char prompt[38];
  sprintf(prompt, "Choose the amount of size %hhu boats: ", size);
  return read_u8(prompt);
}

uint8_t* read_boatamount()
{
  uint8_t* boats = (uint8_t*) malloc((BOAT_MAX_SIZE + 1) * sizeof(uint8_t));
  boats[0] = 0;
  while (boats[0] == 0)
  {
    uint16_t all = 0;
    for (int i = BOAT_MIN_SIZE; i <= BOAT_MAX_SIZE; i++)
    {
      boats[i] = read_amount(i);
      all += boats[i];
    }
    boats[0] = all;

    if (all == 0)
    {
      printf("You must have at least one boat on your game\n");
    }
    else if (boats[0] != all)
    {
      // Overflow detected (u16 vs u8), user past the 255 limit
      printf("You can't have more than 255 boats on your game\n");
      boats[0] = 0;
    }
  }
  return boats;
}

Boat* read_boat(Board* board, int size, int remaining, int total, bool mode)
{
  int x = -1;
  int y = -1;
  while (x < 0 || y < 0 || x >= board->height || y >= board->width)
  {
    // Manual input
    if (mode)
    {
      printf("Choose the coordinates for your next size %d boat\n", size);
      x = read_u8("Vertical coordinate: ");
      y = read_u8("Horizontal coordinate: ");
      if (x < 0 || y < 0 || x >= board->height || y >= board->width)
      {
        printf("Invalid coordinates (%d,%d), you must choose coordinates that fit in your board\n", x, y);
      }
      else if (board->matrix[x][y] != 0)
      {
        printf("Coordinates already in use (%d,%d)\n", x, y);
        x = -1;
        y = -1;
      }
    }
    // Random input
    else
    {
      while (x == -1 || y == -1)
      {
        srand(time(0));
        x = rand() % board->height;
        y = rand() % board->width;

        if (board->matrix[x][y] != 0)
        {
          x = -1;
          y = -1;
        }
      }
    }
  }

  // Do not ask for direction on size 1 boats
  if (size == 1)
  {
    return construct_boat(x, y, size, HORIZONTAL);
  }

  uint8_t d = -1;

  if (mode)
  {
    while (d != HORIZONTAL && d != VERTICAL)
    {
      d = read_u8("What direction do you want to place this boat at (0 = Horizontal, 1 = Vertical): ");
      if (d != HORIZONTAL && d != VERTICAL)
      {
        printf("Invalid direction\n");
      }
    }
  }
  else
  {
    d = rand() % 2;
  }

  return construct_boat(x, y, size, d);
}

void place_boats(Board* board, int size, int total, bool mode)
{
  if (total < 1)
  {
    _logf(L_INFO, "No boats of size %d to place", size);
    return;
  }

  for (int remaining = total; remaining > 0; remaining--)
  {
    Boat* boat = read_boat(board, size, remaining, total, mode);
    if (add_boat(board, boat) == false)
    {
      destruct_boat(boat);
      remaining++;
      continue;
    }
		printf("\n");
    print_board(board);
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  bool config = read_bool("Choose the configuration type (0 = random, 1 = manual): ");
  uint8_t boardsz = read_boardsize();
  uint8_t* boats = read_boatamount();
  Game* game = construct_game(boardsz, boardsz, boats);

  printf("\n");
  printf("Player 1, it's time to set up your board\n");
  printf("\n");
  print_board(game->board_p1);
  printf("\n");

  for (int i = BOAT_MAX_SIZE; i >= BOAT_MIN_SIZE; i--)
  {
    place_boats(game->board_p1, i, boats[i], config);
  }

  printf("\n");
  printf("Player 2, it's time to set up your board\n");
  printf("\n");
  print_board(game->board_p2);
  printf("\n");

  for (int i = BOAT_MAX_SIZE; i >= BOAT_MIN_SIZE; i--)
  {
    place_boats(game->board_p2, i, boats[i], config);
  }

  destruct_game(game);
  return 0;
}
