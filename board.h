#include <stdlib.h>
#include <stdio.h>
#include "boat.h"


typedef struct
{
  int   height;
  int   width;
  int** matrix;
} Board;

Board* mk_board(int height, int width);
void print_board(Board* board);
