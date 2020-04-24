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

void print_board(Board* board, bool obfuscate)
{
  // Table headers
  printf("   | ");
  for (uint8_t x = 0; x < board->height; x++)
  {
    printf("%02hhu ", x);
  }
  printf("\n");

  printf("---+");
  for (uint8_t x = 0; x < board->height; x++)
  {
    printf("---");
  }
  printf("\n");


  // Table content
  for (uint8_t x = 0; x < board->height; x++)
  {
    printf("%02hhu | ", x);
    for (uint8_t y = 0; y < board->width; y++)
    {
      if (board->matrix[x][y] == 0)
      {
        printf("~~ ");
      }
      else if (board->matrix[x][y] == 'x' || board->matrix[x][y] == 'X')
      {
        printf("%c%c ", board->matrix[x][y], board->matrix[x][y]);
      }
      else if (!obfuscate)
      {
        printf("%hhu%hhu ", board->matrix[x][y], board->matrix[x][y]);
      }
      else if (obfuscate)
      {
        printf("~~ ");
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

  /*
  // Verify if boat's points won't overlap any used board coordinates
  for (uint8_t i = 0; i < boat->size; i++)
  {
    if (board->matrix[boat->points[i]->x][boat->points[i]->y] != 0)
    {
      return false;
    }
  }

  // Update board's quick access matrix
  for (uint8_t i = 0; i < boat->size; i++)
  {
    board->matrix[boat->points[i]->x][boat->points[i]->y] = boat->size;
  }

  // Push new boat to board boat array
  board->boats[board->cur_boat] = boat;
  // Internal pointer for boats array
  board->cur_boat++;
  */

  _logf(L_INFO, "Added boat with type %hhu to board", boat->type);
  return true;
}

// TODO: Different shape checks
bool can_add_boat(Board* board, uint8_t x, uint8_t y, uint8_t size, Rotation rotation)
{
  // Out of boundaries
  if (x + size - 1 >= board->height || y + size - 1 >= board->width)
  {
    return false;
  }

  // Verify if boat's points won't overlap any used board coordinates
  if (rotation == ROTATION_0)
  {
    for (uint8_t i = 0, t = y; t < y + size; t++, i++)
    {
      if (board->matrix[x][t] != 0)
      {
        return false;
      }
    }
  }
  else if (rotation == ROTATION_90)
  {
    for (uint8_t i = 0, t = x; t < x + size; t++, i++)
    {
      if (board->matrix[x][t] != 0)
      {
        return false;
      }
    }
  }

  return true;
}

bool verify_state(uint8_t height, uint8_t width, uint8_t** matrix)
{
  for (int x = 0; x < height; x++)
  {
    for (int y = 0; y < width; y++)
    {
      // Game still not over
      if (matrix[x][y] != 0x0 && matrix[x][y] != 'x' && matrix[x][y] != 'X')
      {
        _logf(L_INFO, "verify_state: Found %c at %hhu, %hhu", matrix[x][y], x, y);
        return false;
      }
    }
  }
  // Game over
  return true;
}
