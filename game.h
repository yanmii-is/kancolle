#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "board.h"


typedef struct
{
  bool   state;
  int*   boats;
  Board* board_p1;
  Board* board_p2;
} Game;

Game* mk_game(int height, int width, int* boats);
void print_game(Game* game);
