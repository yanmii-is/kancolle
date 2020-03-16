#include "board.h"


Board* construct_board(uint8_t height, uint8_t width, uint16_t boats)
{
  Board* ret;

  if (height == 0 || width == 0)
  {
    _logf(L_FATAL, "Cannot create a board with zero size (%hhu, %hhu)", height, width);
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
  ret->boats = (Boat**) malloc(boats * sizeof(Boat*));
  ret->cur_boat = 0;
  _logf(L_INFO, "Board created with size %hhux%hhu for %hu boats", height, width, boats);
  return ret;
}

void destruct_board(Board* board)
{
  _logf(L_INFO, "Board (%hhu, %hhu) destructed", board->height, board->width);
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

bool add_boat(Board* board, Boat* boat)
{
  if (board == NULL || boat == NULL)
  {
    return false;
  }

  // Verify if boat's points won't overlap any used board coordinates
  for (int i = 0; i < boat->size; i++)
  {
    if (board->matrix[boat->points[i]->x][boat->points[i]->y] != 0)
    {
      return false;
    }
  }

  // Update board's quick access matrix
  for (int i = 0; i < boat->size; i++)
  {
    board->matrix[boat->points[i]->x][boat->points[i]->y] = boat->size;
  }

  // Push new boat to board boat array
  board->boats[board->cur_boat] = boat;
  // Internal pointer for boats array
  board->cur_boat++;

  _logf(L_INFO, "Added boat with size %hhu to board", boat->size);
  return true;
}
