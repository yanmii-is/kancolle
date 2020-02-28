#include "board.h"


Board* mk_board(int height, int width)
{
  Board* ret = malloc(sizeof(Board));
  ret->height = height;
  ret->width = width;
  ret->matrix = (int**) malloc(height * sizeof(int));
  for (int i = 0; i < height; i++)
  {
    ret->matrix[i] = (int*) malloc(width * sizeof(int));
  }
  for (int x = 0; x < ret->height; x++)
  {
    for (int y = 0; y < ret->width; y++)
    {
      ret->matrix[x][y] = 0;
      //*(*(board->matrix + x) + y) = 1;
    }
  }
  return ret;
}

void print_board(Board* board)
{
  for (int x = 0; x < board->height; x++)
  {
    for (int y = 0; y < board->width; y++)
    {
      printf("%d ", board->matrix[x][y]);
    }
    printf("\n");
  }
}
