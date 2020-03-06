#include <stdlib.h>
#include <stdio.h>
#include "boat.h"


typedef struct
{
  int   height;
  int   width;
  int** matrix;
} Board;

Board* construct_board(int height, int width);
void destruct_board(Board* board);
void print_board(Board* board);
