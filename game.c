#include "game.h"


Game* game_construct(u8 height, u8 width)
{
  Game* ret;

  ret = malloc(sizeof(Game));
  ret->state = 0;
  ret->board_p1 = board_construct(height, width);
  ret->board_p2 = board_construct(height, width);

  if (ret->board_p1 == NULL || ret->board_p2 == NULL)
  {
    _logf(L_FATAL, "Board creation failed, cannot initialize game");
    return NULL;
  }

  _logf(L_INFO, "Game created");
  return ret;
}

void game_destruct(Game* game)
{
  board_destruct(game->board_p1);
  board_destruct(game->board_p2);

  _logf(L_INFO, "Game with state %hhu destructed", game->state);
  free(game);
  return;
}

void game_print(Game* game)
{
  printf("State: %hhu\n", game->state);
  // printf("Board 1:\n");
  // print_board(game->board_p1);
  // printf("Board 2:\n");
  // print_board(game->board_p2);
}

bool game_verify(Game* game, u8 player)
{
  Board* board;

  if (player != 1 && player != 2)
  {
    return false;
  }

  board = (player == 1) ? game->board_p1 : game->board_p2;

  for (u8 x = 0; x < board->height; x++)
  {
    for (u8 y = 0; y < board->width; y++)
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
