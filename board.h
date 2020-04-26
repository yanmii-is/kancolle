#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "boat.h"
#include "cell.h"

typedef struct
{
  uint8_t  height;
  uint8_t  width;
  Cell**   matrix;
} Board;

Board* construct_board (uint8_t height, uint8_t width);
void destruct_board    (Board* board);
void print_board       (Board* board, bool obfuscate);
bool add_boat          (Board* board, Boat* boat);
bool verify_state      (uint8_t height, uint8_t width, Cell** matrix);
