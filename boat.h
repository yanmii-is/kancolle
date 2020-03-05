#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct
{
  int x;
  int y;
  int size;
} Boat;

Boat* mk_boat(int x, int y, int size);
