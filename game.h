#include <stdbool.h>
#include <stdlib.h>


typedef struct
{
  int** board;
} Board;

Board* mk_board(int height, int width);


typedef struct
{
  bool   state;
  Board* board_p1;
  Board* board_p2;
} Game;

Game* mk_game(int height, int width);
