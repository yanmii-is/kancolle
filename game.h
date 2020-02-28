#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
  bool  state;
  int** board;
} Game;

Game* mk_game(int height, int width);
