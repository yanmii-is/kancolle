#include <stdio.h>
#include "game.h"


int main(int argc, char *argv[])
{
  if (argc >= 2)
  {
    printf("%d argument(s)\n", argc-1);
  }

  mk_game(10, 10);
  return 0;
}
