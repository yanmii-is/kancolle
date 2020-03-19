#pragma once
#include <stdint.h>
#include <stdlib.h>
#include "log.h"


typedef struct {
  uint8_t x;
  uint8_t y;
} Point;

Point* construct_point(uint8_t x, uint8_t y);
void destruct_point(Point* point);
