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
  if (direction == HORIZONTAL)
  {
    for (uint8_t i = 0, t = y; t < y + size; t++, i++)
    {
      ret->points[i] = construct_point(x, t);
    }
  }
  else if (direction == VERTICAL)
  {
    for (uint8_t i = 0, t = x; t < x + size; t++, i++)
    {
      ret->points[i] = construct_point(t, y);
    }
  }
  ret->size = size;
  ret->direction = direction;
  _logf(L_INFO, "Boat constructed at (%d, %d) with size %d and direction %d", x, y, size, direction);
  return ret;
}

void destruct_boat(Boat* boat)
{
  // Destruct boat's points first
  for (uint8_t i = 0; i < boat->size; i++)
  {
    free(boat->points[i]);
  }
  free(boat->points);

  _logf(L_INFO, "Boat destructed with size %d and direction %d", boat->size, boat->direction);
  free(boat);
  return;
}
