#include "boat.h"


Boat* construct_boat(uint8_t x, uint8_t y, uint8_t size, Direction direction)
{
  Boat* ret;

  if (size == 0)
  {
    _logf(L_FATAL, "Cannot create a boat with no size or negative size (%d)", size);
    return NULL;
  }

  ret = malloc(sizeof(Boat));
  ret->points = (Point**) malloc(size * sizeof(Point*));
  for (uint8_t i = 0; i < size; i++)
  {
    if (direction == HORIZONTAL)
    {
      for (uint8_t t = y; y < y + size; t++)
      {
        ret->points[i] = construct_point(x, t);
      }
    }
    else if (direction == VERTICAL)
    {
      for (uint8_t t = x; x < x + size; t++)
      {
        ret->points[i] = construct_point(t, y);
      }
    }
  }
  ret->size = size;
  ret->direction = direction;
  _logf(L_INFO, "Boat constructed at (%d, %d) with size %d and direction %d\n", x, y, size, direction);
  return ret;
}

void destruct_boat(Boat* boat)
{
  _logf(L_INFO, "Boat destructed with size %d and direction %d\n", boat->size, boat->direction);
  free(boat);
  return;
}
