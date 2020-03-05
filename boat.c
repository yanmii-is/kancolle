#include "boat.h"


Boat* mk_boat(int x, int y, int size) {
  Boat* ret = malloc(sizeof(Boat));
  ret->x = x;
  ret->y = y;
  ret->size = size;
  printf("[!] Boat created at (%d, %d) with size %d\n", x, y, size);
  return ret;
}
