#include "game.h"

Game* mk_game(int height, int width)
{
  Game* ret = malloc(sizeof(Game));
  ret->state = false;
  ret->board = (int**) malloc(height * sizeof(int));
  for (int i = 0; i < height; i++)
  {
    ret->board[i] = (int*) malloc(width * sizeof(int));
  }
  return ret;
}
