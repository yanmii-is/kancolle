#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "boat.h"
#include "cell.h"

typedef struct
{
  uint8_t  height;
  uint8_t  width;
  Cell*    matrix;
} Board;

Board* board_construct  (uint8_t height, uint8_t width);
void   board_destruct   (Board* board);
void   board_print      (Board* board, bool obfuscate);
bool   board_add        (Board* board, Boat* boat, uint8_t x, uint8_t y);
bool   board_attack     (Board* board, uint8_t x, uint8_t y);
