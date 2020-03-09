#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "board.h"


typedef struct
{
  bool   state;
  int*   boats;
  Board* board_p1;
  Board* board_p2;
} Game;

Game* construct_game(uint8_t height, uint8_t width, int* boats);
void destruct_game(Game* game);
void print_game(Game* game);
