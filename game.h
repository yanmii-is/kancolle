#include <stdbool.h>
#include <stdlib.h>
#include "board.h"

typedef struct
{
  bool   state;
  Board* board_p1;
  Board* board_p2;
} Game;

Game* mk_game(int height, int width);
