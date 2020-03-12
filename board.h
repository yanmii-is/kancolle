#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "boat.h"


typedef struct
{
  uint8_t   height;
  uint8_t   width;
  uint8_t** matrix;
  Boat**    boats;
  uint8_t   cur_boat;
} Board;

Board* construct_board(uint8_t height, uint8_t width, uint16_t boats);
void destruct_board(Board* board);
void print_board(Board* board);
bool add_boat(Board* board, Boat* boat);
