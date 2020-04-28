#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "board.h"
#include "config.h"

typedef struct
{
  u8      state;
  Board*  board_p1;
  Board*  board_p2;
} Game;

Game* game_construct  (u8 height, u8 width);
void  game_destruct   (Game* game);
void  game_print      (Game* game);
bool  game_verify     (Game* game, u8 player);
