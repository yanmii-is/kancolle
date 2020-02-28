#include "game.h"


Game* mk_game(int height, int width)
{
  Game* ret = malloc(sizeof(Game));
  ret->state = false;
  ret->board_p1 = mk_board(height, width);
  ret->board_p2 = mk_board(height, width);
  return ret;
}

Board* mk_board(int height, int width)
{
  Board* ret = malloc(sizeof(Board));
  ret->board = (int**) malloc(height * sizeof(int));
  for (int i = 0; i < height; i++)
  {
    ret->board[i] = (int*) malloc(width * sizeof(int));
  }
  return ret;
}
