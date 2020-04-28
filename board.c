#include "board.h"


Board* board_construct(u8 height, u8 width)
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

  for (u8 x = 0; x < height; x++)
  {
    for (u8 y = 0; y < width; y++)
    {
      ret->matrix[x * height + y].boat = 0x0;
      ret->matrix[x * height + y].shot = 0;
    }
  }

  _logf(L_INFO, "Board created with size %hhux%hhu", height, width);
  return ret;
}

void board_destruct(Board* board)
{
  _logf(L_INFO, "Board (%hhu, %hhu) destructed", board->height, board->width);
  free(board->matrix);
  free(board);
  return;
}

void board_print(Board* board, bool obfuscate)
{
  // Table headers
  printf("   | ");
  for (u8 x = 0; x < board->height; x++)
  {
    printf("%02hhu ", x);
  }
  printf("\n");

  printf("---+");
  for (u8 x = 0; x < board->height; x++)
  {
    printf("---");
  }
  printf("\n");


  // Table content
  for (u8 x = 0; x < board->height; x++)
  {
    printf("%02hhu | ", x);
    for (u8 y = 0; y < board->width; y++)
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

bool board_add(Board* board, Boat* boat, u8 x, u8 y)
{
  if (board == NULL || boat == NULL)
  {
    return false;
  }

  // Verify if Boat won't overlap any used Board coordinates
  for (u8 i = x; i <= x+5; i++)
  {
    for (u8 j = y; j <= y+5; j++)
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
  for (u8 i = x; i <= x+5; i++)
  {
    for (u8 j = y; j <= y+5; j++)
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

bool board_attack(Board* board, u8 x, u8 y)
{
  if (board->matrix[x * board->height + y].boat == 0x0)
  {
    printf("You hit the sea...\n");
    board->matrix[x * board->height + y].shot = 1;
    return false;
  }
  else
  {
    printf("You hit something!\n");
    board->matrix[x * board->height + y].shot = 2;
    board->matrix[x * board->height + y].boat->damage++;
    return true;
  }
}
