#include <stdlib.h>


typedef struct
{
  int** board;
} Board;

Board* mk_board(int height, int width);
