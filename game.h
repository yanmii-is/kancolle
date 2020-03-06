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

Game* construct_game(int height, int width, int* boats);
void destruct_game(Game* game);
void print_game(Game* game);
