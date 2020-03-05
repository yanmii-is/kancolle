#include <stdio.h>
#include "game.h"


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

Boat* read_boat(int size, int remaining, int total)
{
  int x = 0;
  int y = 0;
  while (x <= 0 || y <= 0)
  {
    printf("Player 1, choose the coordinates for your next size %d boat as \"x,y\" (%d/%d): ", size, remaining, total);
    scanf("%d,%d", &x, &y);
    if (x <= 0 || y <= 0)
    {
      printf("Invalid coordinates (%d,%d), you must choose positive coordinates and input them as \"x,y\"\n", x, y);
    }
  }
  mk_boat(x, y, size);
}

int main(int argc, char *argv[])
{
  if (argc >= 2)
  {
    printf("%d argument(s)\n", argc-1);
  }

  int n = 0;
  while (n < 4 || n > 99)
  {
    printf("Choose the board size: ");
    scanf("%d", &n);
    if (n < 4 || n > 99)
    {
      printf("Invalid size (%dx%d), a board must be between 4x4 and 99x99\n", n, n);
    }
  }

  int b1 = read_amount(1);
  int b2 = read_amount(2);
  int b3 = read_amount(3);
  int b4 = read_amount(4);

  Game* game = mk_game(n, n, b1, b2, b3, b4);
  print_game(game);
  printf("\n");

  print_board(game->board_p1);
  printf("\n");


  for (int current = b4; current > 0; current--)
  {
    Boat* boat = read_boat(4, current, b4);
    // TODO: Sanity checks
    // TODO: Add boat to board
  }

  return 0;
}
