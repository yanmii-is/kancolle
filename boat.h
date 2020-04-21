#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "point.h"
#include "log.h"


typedef enum {ROTATION_0, ROTATION_90, ROTATION_180, ROTATION_270} Rotation;
typedef enum {TYPE_LINEAR_1, TYPE_LINEAR_2, TYPE_LINEAR_3, TYPE_LINEAR_4, TYPE_TSHAPE_5} Type;

typedef struct
{
  Point** points;
  Type type;
  Rotation rotation;
  uint8_t size;
} Boat;

Boat* construct_boat(uint8_t x, uint8_t y, uint8_t size, Rotation rotation);
void destruct_boat(Boat* boat);
