#include <stdio.h>
#include "game.h"


int read_input(int size)
{
  int boats = 0;
  while (boats < 1)
  {
    printf("Choose the amount of size %d boats: ", size);
    scanf("%d", &boats);
    if (boats < 1)
    {
      printf("Invalid amount (%d)\n", boats);
    }
  }
  return boats;
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

  int b1 = read_input(1);
  int b2 = read_input(2);
  int b3 = read_input(3);
  int b4 = read_input(4);

  Game* game = mk_game(n, n, b1, b2, b3, b4);
  // print_game(game);

  printf("Player 1, choose your boats: \n");
  print_board(game->board_p1);

  return 0;
}
