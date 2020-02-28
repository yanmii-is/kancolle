#include "game.h"


Game* mk_game(int height, int width)
{
  Game* ret = malloc(sizeof(Game));
  ret->state = false;
  ret->board_p1 = mk_board(height, width);
  ret->board_p2 = mk_board(height, width);
  return ret;
}
