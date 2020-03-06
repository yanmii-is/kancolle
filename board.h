#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "boat.h"


typedef struct
{
  uint8_t   height;
  uint8_t   width;
  uint8_t** matrix;
} Board;

Board* construct_board(uint8_t height, uint8_t width);
void destruct_board(Board* board);
void print_board(Board* board);
