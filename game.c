#include "game.h"


Game* mk_game(int height, int width, int b1, int b2, int b3, int b4)
{
  Game* ret = malloc(sizeof(Game));
  ret->state = false;
  ret->b1 = b1;
  ret->b2 = b2;
  ret->b3 = b3;
  ret->b4 = b4;
  ret->board_p1 = mk_board(height, width);
  ret->board_p2 = mk_board(height, width);
  return ret;
}

void print_game(Game* game)
{
  printf("State: %s\n", game->state ? "true" : "false");
  printf("Boats: %d | %d | %d | %d\n", game->b1, game->b2, game->b3, game->b4);
  // TODO: print_board
}
