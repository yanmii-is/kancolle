#include "game.h"


Game* construct_game(uint8_t height, uint8_t width, int* boats)
{
  Game* ret;

  if (height == 0 || width == 0)
  {
    _logf(L_FATAL, "Cannot create a game with zero or negative size boards (%hhu, %hhu)\n", height, width);
    return NULL;
  }
  if (boats[1] + boats[2] + boats[3] + boats[4] + boats[5] == 0)
  {
    _logf(L_FATAL, "Cannot create a game with no boats\n");
    return NULL;
  }

  ret = malloc(sizeof(Game));
  ret->state = false;
  ret->boats = boats;
  ret->board_p1 = construct_board(height, width);
  ret->board_p2 = construct_board(height, width);
  _logf(L_INFO, "Game created with boat limits %hhu | %hhu | %hhu | %hhu | %hhu\n", boats[1], boats[2], boats[3], boats[4], boats[5]);
  return ret;
}

void destruct_game(Game* game)
{
  destruct_board(game->board_p1);
  destruct_board(game->board_p2);
  _logf(L_INFO, "Game with state %s and limits %hhu | %hhu | %hhu | %hhu destructed\n",
        game->state ? "true" : "false", game->boats[1], game->boats[2], game->boats[3], game->boats[4], game->boats[5]);
  free(game);
  return;
}

void print_game(Game* game)
{
  printf("State: %s\n", game->state ? "true" : "false");
  printf("Boats: %hhu | %hhu | %hhu | %hhu\n", game->boats[1], game->boats[2], game->boats[3], game->boats[4], game->boats[5]);
  // printf("Board 1:\n");
  // print_board(game->board_p1);
  // printf("Board 2:\n");
  // print_board(game->board_p2);
}
