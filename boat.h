#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "log.h"

typedef enum {HORIZONTAL, VERTICAL} Direction;

typedef struct
{
  uint8_t x;
  uint8_t y;
  uint8_t size;
  Direction direction;
  // TODO: Non-rectangular boats
} Boat;

Boat* construct_boat(uint8_t x, uint8_t y, uint8_t size, Direction direction);
void destruct_boat(Boat* boat);
