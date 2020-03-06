#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"

typedef enum {HORIZONTAL, VERTICAL} Direction;

typedef struct
{
  int x;
  int y;
  int size;
  Direction direction;
  // TODO: Non-rectangular boats
} Boat;

Boat* construct_boat(int x, int y, int size, Direction direction);
void destruct_boat(Boat* boat);
