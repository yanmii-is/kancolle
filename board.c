#include "board.h"


Board* construct_board(int height, int width)
{
  Board* ret;

  if (height <= 0 || width <= 0)
  {
    _logf(L_FATAL, "Cannot create a board with zero or negative size (%d, %d)\n", height, width);
    return NULL;
  }

  ret = malloc(sizeof(Board));
  ret->height = height;
  ret->width = width;
  ret->matrix = (int**) malloc(width * sizeof(int*));
  for (int i = 0; i < height; i++)
  {
    ret->matrix[i] = (int*) malloc(height * sizeof(int));
  }
  for (int x = 0; x < height; x++)
  {
    for (int y = 0; y < width; y++)
    {
      ret->matrix[x][y] = 0;
      //*(*(ret->matrix + x) + y) = 0;
    }
  }
  _logf(L_INFO, "Board created with size %dx%d\n", height, width);
  return ret;
}

void destruct_board(Board* board)
{
  _logf(L_INFO, "Board (%d, %d) destructed\n", board->height, board->width);
  free(board);
  return;
}

void print_board(Board* board)
{
  // Table headers
  printf("   | ");
  for (int x = 0; x < board->height; x++)
  {
    printf("%02d ", x);
  }
  printf("\n");

  printf("---+");
  for (int x = 0; x < board->height; x++)
  {
    printf("---");
  }
  printf("\n");


  // Table content
  for (int x = 0; x < board->height; x++)
  {
    printf("%02d | ", x);
    for (int y = 0; y < board->width; y++)
    {
      if (board->matrix[x][y] == 0)
      {
        printf("~~ ");
      }
      else
      {
        printf("%d%d ", board->matrix[x][y], board->matrix[x][y]);
      }

    }
    printf("\n");
  }
}
