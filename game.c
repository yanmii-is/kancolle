#include "game.h"


Game* construct_game(int height, int width, int* boats)
{
  Game* ret = malloc(sizeof(Game));
  ret->state = false;
  ret->boats = boats;
  ret->board_p1 = construct_board(height, width);
  ret->board_p2 = construct_board(height, width);
  _logf(L_INFO, "Game created with boat limits %d | %d | %d | %d | %d\n", boats[1], boats[2], boats[3], boats[4], boats[5]);
  return ret;
}

void destruct_game(Game* game)
{
  destruct_board(game->board_p1);
  destruct_board(game->board_p2);
  _logf(L_INFO, "Game with state %s and limits %d | %d | %d | %d destructed\n",
        game->state ? "true" : "false", game->boats[1], game->boats[2], game->boats[3], game->boats[4], game->boats[5]);
  free(game);
  return;
}

void print_game(Game* game)
{
  printf("State: %s\n", game->state ? "true" : "false");
  printf("Boats: %d | %d | %d | %d\n", game->boats[1], game->boats[2], game->boats[3], game->boats[4], game->boats[5]);
  // printf("Board 1:\n");
  // print_board(game->board_p1);
  // printf("Board 2:\n");
  // print_board(game->board_p2);
}
