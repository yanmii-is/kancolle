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
  _logf(L_INFO, "Game created with boat limits %d | %d | %d | %d\n", b1, b2, b3, b4);
  return ret;
}

void print_game(Game* game)
{
  printf("State: %s\n", game->state ? "true" : "false");
  printf("Boats: %d | %d | %d | %d\n", game->b1, game->b2, game->b3, game->b4);
  // printf("Board 1:\n");
  // print_board(game->board_p1);
  // printf("Board 2:\n");
  // print_board(game->board_p2);
}
