#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "log.h"

typedef enum {
  ROTATION_0, ROTATION_90, ROTATION_180, ROTATION_270
} BoatRotation;

typedef enum {
  NONE, TYPE_LINEAR_1, TYPE_LINEAR_2, TYPE_LINEAR_3, TYPE_LINEAR_4, TYPE_TSHAPE_5
} BoatType;

extern uint8_t bitmap_TL1[5][5];
extern uint8_t bitmap_TL2[5][5];
extern uint8_t bitmap_TL3[5][5];
extern uint8_t bitmap_TL4[5][5];
extern uint8_t bitmap_TT5[5][5];

typedef struct
{
  BoatType      type;
  BoatRotation  rotation;
  uint8_t       bitmap[5][5];  // 0: Empty, 1: NoHit, 2: Hit, 3: Miss
  uint8_t       damage;
} Boat;

Boat* boat_construct  (BoatType type, BoatRotation rotation);
void  boat_destruct   (Boat* boat);
void  boat_print      (Boat* boat);
void  boat_rotate     (Boat* boat);
