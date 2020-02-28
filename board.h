#include <stdlib.h>
#include "fleet.h"


typedef struct
{
  int** board;
} Board;

Board* mk_board(int height, int width);
