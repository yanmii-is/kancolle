#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "log.h"

typedef enum {
  ROTATION_0, ROTATION_90, ROTATION_180, ROTATION_270
} BoatRotation;

typedef enum {
  TYPE_LINEAR_1, TYPE_LINEAR_2, TYPE_LINEAR_3, TYPE_LINEAR_4, TYPE_TSHAPE_5
} BoatType;

typedef struct
{
  uint8_t**    bitmap;
  BoatType     type;
  BoatRotation rotation;
} Boat;

extern uint8_t bitmap_TL1[5][5];
extern uint8_t bitmap_TL2[5][5];
extern uint8_t bitmap_TL3[5][5];
extern uint8_t bitmap_TL4[5][5];
extern uint8_t bitmap_TT5[5][5];

Boat* construct_boat (uint8_t x, uint8_t y, BoatType type, BoatRotation rotation);
void  destruct_boat  (Boat* boat);
