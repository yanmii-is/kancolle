#include "board.h"


Board* mk_board(int height, int width)
{
  Board* ret = malloc(sizeof(Board));
  ret->board = (int**) malloc(height * sizeof(int));
  for (int i = 0; i < height; i++)
  {
    ret->board[i] = (int*) malloc(width * sizeof(int));
  }
  return ret;
}
