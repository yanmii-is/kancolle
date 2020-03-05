#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"

typedef struct
{
  int x;
  int y;
  int size;
  // TODO: Non-rectangular boats
} Boat;

Boat* mk_boat(int x, int y, int size);
