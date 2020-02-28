#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"


typedef struct
{
  bool   state;
  int    b1;
  int    b2;
  int    b3;
  int    b4;
  Board* board_p1;
  Board* board_p2;
} Game;

Game* mk_game(int height, int width, int b1, int b2, int b3, int b4);
void print_game(Game* game);
