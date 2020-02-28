#include "boat.h"


Boat* mk_boat(int size) {
  Boat* ret = malloc(sizeof(Boat));
  ret->size = size;
  return ret;
}
