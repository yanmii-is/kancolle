#pragma once
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "boat.h"
#include "cell.h"

typedef struct
{
  u8     height;
  u8     width;
  Cell*  matrix;
} Board;

Board*       board_construct  (u8 height, u8 width);
return_code  board_destruct   (Board* board);
return_code  board_print      (Board* board, bool obfuscate);
return_code  board_add        (Board* board, Boat* boat, s16 x, s16 y);
