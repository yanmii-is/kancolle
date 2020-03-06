#include "boat.h"


Boat* construct_boat(int x, int y, int size, Direction direction)
{
  Boat* ret;

  if (x < 0 || y < 0)
  {
    _logf(L_FATAL, "Cannot create a boat on negative coordinates (%d, %d)", x, y);
    return NULL;
  }
  if (size <= 0)
  {
    _logf(L_FATAL, "Cannot create a boat with no size or negative size (%d)", size);
    return NULL;
  }

  ret = malloc(sizeof(Boat));
  ret->x = x;
  ret->y = y;
  ret->size = size;
  ret->direction = direction;
  _logf(L_INFO, "Boat constructed at (%d, %d) with size %d and direction %d\n", x, y, size, direction);
  return ret;
}

void destruct_boat(Boat* boat)
{
  _logf(L_INFO, "Boat destroyed at (%d, %d) with size %d and direction %d\n", boat->x, boat->y, boat->size, boat->direction);
  free(boat);
  return;
}
