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
  mk_boat(x, y, size);
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

  // read_boat: Size 4
  for (int current = b4; current > 0; current--)
  {
    Boat* boat = read_boat(game->board_p1, 4, current, b4);
    game->board_p1->matrix[boat->x][boat->y] = 4; // TODO
    print_board(game->board_p1);
    // TODO: Sanity checks
    // TODO: Add boat to board
  }

  // read_boat: Size 3
  for (int current = b3; current > 0; current--)
  {
    Boat* boat = read_boat(game->board_p1, 3, current, b3);
    game->board_p1->matrix[boat->x][boat->y] = 3; // TODO
    print_board(game->board_p1);
    // TODO: Sanity checks
    // TODO: Add boat to board
  }

  // read_boat: Size 2
  for (int current = b2; current > 0; current--)
  {
    Boat* boat = read_boat(game->board_p1, 2, current, b2);
    game->board_p1->matrix[boat->x][boat->y] = 2; // TODO
    print_board(game->board_p1);
    // TODO: Sanity checks
    // TODO: Add boat to board
  }

  // read_boat: Size 1
  for (int current = b1; current > 0; current--)
  {
    Boat* boat = read_boat(game->board_p1, 1, current, b1);
    game->board_p1->matrix[boat->x][boat->y] = 1; // TODO
    print_board(game->board_p1);
    // TODO: Sanity checks
    // TODO: Add boat to board
  }

  return 0;
}
