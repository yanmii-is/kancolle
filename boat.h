#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "point.h"
#include "log.h"


typedef enum {HORIZONTAL, VERTICAL} Direction;

typedef struct
{
  Point** points;
  uint8_t size;
} Boat;

Boat* construct_boat(uint8_t x, uint8_t y, uint8_t size, Direction direction);
void destruct_boat(Boat* boat);
