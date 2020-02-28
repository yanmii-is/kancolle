#include "board.h"


Board* mk_board(int height, int width)
{
  Board* ret = malloc(sizeof(Board));
  ret->board = (int**) malloc(width * height * sizeof(int));
  return ret;
}
