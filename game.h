#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "board.h"
#include "config.h"

typedef struct
{
  uint8_t  state;
  Board*   board_p1;
  Board*   board_p2;
} Game;

Game* game_construct  (uint8_t height, uint8_t width);
void  game_destruct   (Game* game);
void  game_print      (Game* game);
bool  game_verify     (Game* game, uint8_t player);
