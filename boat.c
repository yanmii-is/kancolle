#include "boat.h"


Boat* mk_boat(int x, int y, int size)
{
  Boat* ret;

  if (x < 0 || y < 0)
  {
    _logf(L_ERROR, "Cannot create a boat on negative coordinates (%d, %d)", x, y);
    return NULL;
  }
  if (size <= 0)
  {
    _logf(L_ERROR, "Cannot create a boat with no size or negative size (%d)", size);
    return NULL;
  }

  ret = malloc(sizeof(Boat));
  ret->x = x;
  ret->y = y;
  ret->size = size;
  _logf(L_INFO, "Boat created at (%d, %d) with size %d\n", x, y, size);
  return ret;
}
