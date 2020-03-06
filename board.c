#include "board.h"


Board* construct_board(uint8_t height, uint8_t width)
{
  Board* ret;

  if (height == 0 || width == 0)
  {
    _logf(L_FATAL, "Cannot create a board with zero size (%hhu, %hhu)\n", height, width);
    return NULL;
  }

  ret = malloc(sizeof(Board));
  ret->height = height;
  ret->width = width;
  ret->matrix = (uint8_t**) malloc(width * sizeof(uint8_t*));
  for (uint8_t i = 0; i < height; i++)
  {
    ret->matrix[i] = (uint8_t*) calloc(height, sizeof(uint8_t));
  }
  _logf(L_INFO, "Board created with size %hhux%hhu\n", height, width);
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
    printf("%02hhu ", x);
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
    printf("%02hhu | ", x);
    for (int y = 0; y < board->width; y++)
    {
      if (board->matrix[x][y] == 0)
      {
        printf("~~ ");
      }
      else
      {
        printf("%hhu%hhu ", board->matrix[x][y], board->matrix[x][y]);
      }
    }
    printf("\n");
  }
}
