#include "board.h"


Board* construct_board(uint8_t height, uint8_t width)
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
  ret->matrix = (Cell*) malloc(width * height * sizeof(Cell));

  for (int x = 0; x < height; x++)
  {
    for (int y = 0; y < width; y++)
    {
      ret->matrix[x * height + y].boat = 0x0;
      ret->matrix[x * height + y].shot = 0;
    }
  }

  _logf(L_INFO, "Board created with size %hhux%hhu", height, width);
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
      if (board->matrix[x * board->height + y].boat == 0x0 && board->matrix[x * board->height + y].shot == 0)
      {
        printf("~~ ");
      }
      else if (board->matrix[x * board->height + y].shot == 1)
      {
        printf("xx ");
      }
      else if (board->matrix[x * board->height + y].shot == 2)
      {
        printf("±± ");
      }
      else if (obfuscate)
      {
        printf("~~ ");
      }
      else if (board->matrix[x * board->height + y].boat != 0x0 && board->matrix[x * board->height + y].shot == 0)
      {
        printf("BB ");
      }
    }
    printf("\n");
  }
}

bool add_boat(Board* board, Boat* boat, uint8_t x, uint8_t y)
{
  if (board == NULL || boat == NULL)
  {
    return false;
  }

  // Verify if Boat won't overlap any used Board coordinates
  for (uint8_t i = x; i <= x+5; i++)
  {
    for (uint8_t j = y; j <= y+5; j++)
    {
      // Ignore unused Boat bitmap coordinates
      if (boat->bitmap[i-x][j-y] == 0)
      {
        continue;
      }

      // Boat overlap detected, pointer to Boat already exists
      if (board->matrix[i * board->height + j].boat != 0x0)
      {
        return false;
      }
    }
  }

  // Update Board's Cell matrix
  for (uint8_t i = x; i <= x+5; i++)
  {
    for (uint8_t j = y; j <= y+5; j++)
    {
      if (boat->bitmap[i-x][j-y] == 1)
      {
        board->matrix[i * board->height + j].boat = boat;
      }
    }
  }

  _logf(L_INFO, "Added boat with type %hhu to board", boat->type);
  return true;
}

bool verify_state(Board* board)
{
  for (int x = 0; x < board->height; x++)
  {
    for (int y = 0; y < board->width; y++)
    {
      // Game still not over (found Boat Cell without hit)
      if (board->matrix[x * board->height + y].boat != 0x0 && board->matrix[x * board->height + y].shot == 0)
      {
        _logf(L_INFO, "verify_state: Found %hhu at %hhu, %hhu", board->matrix[x * board->height + y].shot, x, y);
        return false;
      }
    }
  }
  // Game over
  return true;
}
