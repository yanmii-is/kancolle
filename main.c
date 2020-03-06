#include "game.h"


// TODO: Configuration constants / macros
// TODO: Fortification / sanity checks
// TODO: Get rid of scanf

int read_amount(int size)
{
  int amount = 0;
  while (amount < 1)
  {
    printf("Choose the amount of size %d boats: ", size);
    scanf("%d", &amount);
    if (amount < 1)
    {
      printf("Invalid amount (%d)\n", amount);
    }
  }
  return amount;
}

Boat* read_boat(Board* board, int size, int remaining, int total)
{
  int x = -1;
  int y = -1;
  while (x < 0 || y < 0 || x >= board->height || y >= board->width)
  {
    printf("Player 1, choose the coordinates for your next size %d boat as \"x,y\" (%d/%d): ", size, remaining, total);
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
  int d = -1;
  while (d != HORIZONTAL && d != VERTICAL)
  {
    printf("What direction do you want to place this boat at (%d, %d) (0 = Horizontal, 1 = Vertical): ", x, y);
    scanf("%d", &d);
    if (d != HORIZONTAL && d != VERTICAL)
    {
      printf("Invalid direction\n");
    }
  }
  mk_boat(x, y, size, d);
}

void place_boats(Board* board, int size, int total)
{
  for (int remaining = total; remaining > 0; remaining--)
  {
    Boat* boat = read_boat(board, size, remaining, total);
    // TODO: Boundary checks
    if (boat->direction == HORIZONTAL)
    {
      for (int t = boat->x; t < boat->x + size; t++)
      {
        board->matrix[t][boat->y] = size;
      }
    }
    else if (boat->direction == VERTICAL)
    {
      for (int t = boat->y; t < boat->y + size; t++)
      {
        board->matrix[boat->x][t] = size;
      }
    }
    print_board(board);
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  int n = 0;
  while (n < 4 || n > 100)
  {
    printf("Choose the board size: ");
    scanf("%d", &n);
    if (n < 4 || n > 100)
    {
      printf("Invalid size (%dx%d), a board must be between 4x4 and 100x100\n", n, n);
    }
  }

  int b1 = read_amount(1);
  int b2 = read_amount(2);
  int b3 = read_amount(3);
  int b4 = read_amount(4);

  Game* game = mk_game(n, n, b1, b2, b3, b4);

  printf("\n");
  print_board(game->board_p1);
  printf("\n");

  place_boats(game->board_p1, 4, b4);
  place_boats(game->board_p1, 3, b3);
  place_boats(game->board_p1, 2, b2);
  place_boats(game->board_p1, 1, b1);

  return 0;
}
