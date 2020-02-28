#include <stdio.h>
#include "game.h"


int main(int argc, char *argv[])
{
  if (argc >= 2)
  {
    printf("%d argument(s)\n", argc-1);
  }

  int n = 0;
  while (n < 4)
  {
    printf("Choose the board size: ");
    scanf("%d", &n);
    if (n < 4)
    {
      printf("Invalid size, a board must be at least 4x4");
    }
  }

  mk_game(n, n);
  return 0;
}
