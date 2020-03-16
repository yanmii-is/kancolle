#include "boat.h"


Boat* construct_boat(uint8_t x, uint8_t y, uint8_t size, Direction direction)
{
  Boat* ret;

  // Sanity check
  if (size == 0)
  {
    _logf(L_FATAL, "Cannot create a boat with no size or negative size (%d)", size);
    return NULL;
  }

  // Allocates memory for main Boat structure
  ret = malloc(sizeof(Boat));
  // Allocated memory for Point objects array
  ret->points = (Point**) malloc(size * sizeof(Point*));

  // Construct Point objects and tie the to the current Boat
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

  // Boat size, amount of points
  ret->size = size;

  _logf(L_INFO, "Boat constructed at (%d, %d) with size %d and direction %d", x, y, size, direction);
  return ret;
}

void destruct_boat(Boat* boat)
{
  // Destruct Boat's Point objects first
  for (uint8_t i = 0; i < boat->size; i++)
  {
    free(boat->points[i]);
  }
  // Destruct Point objects array
  free(boat->points);

  _logf(L_INFO, "Boat destructed with size %d", boat->size);
  free(boat);
  return;
}
