#include "game.h"


Game* construct_game(uint8_t height, uint8_t width, uint8_t* boats)
{
  Game* ret;
  uint8_t sum;
  uint8_t max_boats = height * width / 25;

  // Sanity check: board limits
  if (height == 0 || width == 0)
  {
    _logf(L_FATAL, "Cannot create a game with zero or negative size boards (%hhu, %hhu)", height, width);
    return NULL;
  }

  // Sanity check: existance of boats
  if (boats[0] == 0)
  {
    _logf(L_FATAL, "Cannot create a game with no boats");
    return NULL;
  }

  // Sanity check: boats below max_size config
  if (sum > max_boats)
  {
    _logf(L_FATAL, "Cannot create a game with more boats (%d) than the maximum limit (%d)", sum, max_boats);
    return NULL;
  }

  ret = malloc(sizeof(Game));
  ret->state = false;
  ret->boats = boats;
  ret->board_p1 = construct_board(height, width, boats[0]);
  ret->board_p2 = construct_board(height, width, boats[0]);

  _logf(L_INFO, "Game created with %hhu boats", boats[0]);
  return ret;
}

void destruct_game(Game* game)
{
  destruct_board(game->board_p1);
  destruct_board(game->board_p2);
  _logf(L_INFO, "Game with state %s destructed", game->state ? "true" : "false");
  free(game);
  return;
}

void print_game(Game* game)
{
  printf("State: %s\n", game->state ? "true" : "false");
  // printf("Board 1:\n");
  // print_board(game->board_p1);
  // printf("Board 2:\n");
  // print_board(game->board_p2);
}
