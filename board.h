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

Board* board_construct  (u8 height, u8 width);
void   board_destruct   (Board* board);
void   board_print      (Board* board, bool obfuscate);
bool   board_add        (Board* board, Boat* boat, u8 x, u8 y);
bool   board_attack     (Board* board, u8 x, u8 y);
