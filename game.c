#include "game.h"


Game* construct_game(uint8_t height, uint8_t width)
{
  Game* ret;

  ret = malloc(sizeof(Game));
  ret->state = false;
  ret->board_p1 = construct_board(height, width);
  ret->board_p2 = construct_board(height, width);

  if (ret->board_p1 == NULL || ret->board_p2 == NULL)
  {
    _logf(L_FATAL, "Board creation failed, cannot initialize game");
    return NULL;
  }

  _logf(L_INFO, "Game created");
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

bool verify_state(Game* game, uint8_t player)
{
  Board* board;

  if (player != 1 && player != 2)
  {
    return false;
  }

  board = (player == 1) ? game->board_p1 : game->board_p2;

  for (int x = 0; x < board->height; x++)
  {
    for (int y = 0; y < board->width; y++)
    {
      // Game still not over (found Boat Cell without hit)
      if (board->matrix[x * board->height + y].boat != 0x0 && board->matrix[x * board->height + y].shot == 0)
      {
        _logf(L_INFO, "verify_state: Found %hhu at %hhu, %hhu", board->matrix[x * board->height + y].shot, x, y);
        return false;
      }
    }
  }
  // Game over
  game->state = true;
  return true;
}
