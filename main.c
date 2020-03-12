#include "game.h"


// TODO: Configuration constants / macros
// TODO: Fortification / sanity checks
// TODO: Get rid of scanf!!!

uint8_t read_boardsize()
{
  uint8_t ret = 0;
  while (ret < 5 || ret > 100)
  {
    printf("Choose the board size: ");
    scanf("%hhu", &ret);
    if (ret < 5 || ret > 100)
    {
      printf("Invalid size (%dx%d), a board must be between 5x5 and 100x100\n", ret, ret);
    }
  }
  return ret;
}

int read_amount(int size)
{
  int amount = -1;
  while (amount < 0)
  {
    printf("Choose the amount of size %d boats: ", size);
    scanf("%d", &amount);
    if (amount < 0)
    {
      printf("Invalid amount (%d)\n", amount);
    }
  }
  return amount;
}

Boat* read_boat(Board* board, int size, int remaining, int total, int8_t mode)
{
  int x = -1;
  int y = -1;
  while (x < 0 || y < 0 || x >= board->height || y >= board->width)
  {
    // Manual inupt
    if (mode == 1)
    {
      printf("Choose the coordinates for your next size %d boat as \"x,y\" (%d/%d): ", size, remaining, total);
      scanf("%d,%d", &x, &y);
      if (x < 0 || y < 0 || x >= board->height || y >= board->width)
      {
        printf("Invalid coordinates (%d,%d), you must choose coordinates that fit in your board and input them as \"x,y\"\n", x, y);
      }
      else if (board->matrix[x][y] != 0)
      {
        printf("Coordinates already in use (%d,%d), input unused coordinates as \"x,y\"\n", x, y);
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

  int d = -1;

  if(mode == 1)
  {
    while (d != HORIZONTAL && d != VERTICAL)
    {
      printf("What direction do you want to place this boat at (%d, %d) (0 = Horizontal, 1 = Vertical): ", x, y);
      scanf("%d", &d);
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

void place_boats(Board* board, int size, int total, int8_t mode)
{
  if (total < 1)
  {
    _logf(L_INFO, "No boats of size %d to place\n", size);
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
  int8_t config_type = -1;
  while (config_type != 0 && config_type != 1)
  {
    printf("Choose the configuration type (0 = random configuration, 1 = manual configuration): ");
    scanf("%hhd", &config_type);
    if (config_type != 0 && config_type != 1)
    {
      printf("Invalid configuration type %hhd", config_type);
      config_type = -1;
    }
  }

  uint8_t boardsz = read_boardsize();

  int all = 0;
  int* boats = (int*) malloc(6 * sizeof(int));
  while (all == 0)
  {
    boats[1] = read_amount(1);
    boats[2] = read_amount(2);
    boats[3] = read_amount(3);
    boats[4] = read_amount(4);
    boats[5] = read_amount(5);
    all = boats[1] + boats[2] + boats[3] + boats[4] + boats[5];
    if (all == 0)
    {
      printf("You must have at least one boat on your game\n");
    }
  }

  Game* game = construct_game(boardsz, boardsz, boats);

  printf("\n");
  printf("Player 1, it's time to set up your board\n");
  printf("\n");
  print_board(game->board_p1);
  printf("\n");

  place_boats(game->board_p1, 5, boats[5], config_type);
  place_boats(game->board_p1, 4, boats[4], config_type);
  place_boats(game->board_p1, 3, boats[3], config_type);
  place_boats(game->board_p1, 2, boats[2], config_type);
  place_boats(game->board_p1, 1, boats[1], config_type);

  printf("\n");
  printf("Player 2, it's time to set up your board\n");
  printf("\n");
  print_board(game->board_p2);
  printf("\n");

  place_boats(game->board_p2, 5, boats[5], config_type);
  place_boats(game->board_p2, 4, boats[4], config_type);
  place_boats(game->board_p2, 3, boats[3], config_type);
  place_boats(game->board_p2, 2, boats[2], config_type);
  place_boats(game->board_p2, 1, boats[1], config_type);

  destruct_game(game);
  return 0;
}
