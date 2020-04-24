#include "boat.h"

// Presets
uint8_t bitmap_TL1[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
uint8_t bitmap_TL2[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
uint8_t bitmap_TL3[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
uint8_t bitmap_TL4[5][5] = {
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
uint8_t bitmap_TT5[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 }
};


Boat* construct_boat(uint8_t x, uint8_t y, Type type, Rotation rotation)
{
  Boat* ret;

  // Allocates memory for main Boat structure
  ret = malloc(sizeof(Boat));

  /*
  // Allocated memory for Point objects array
  ret->points = (Point**) malloc(size * sizeof(Point*));

  // Construct Point objects and tie the to the current Boat
  if (rotation == ROTATION_0)
  {
    for (uint8_t i = 0, t = y; t < y + size; t++, i++)
    {
      ret->points[i] = construct_point(x, t);
    }
  }
  else if (rotation == ROTATION_90)
  {
    for (uint8_t i = 0, t = x; t < x + size; t++, i++)
    {
      ret->points[i] = construct_point(t, y);
    }
  }
  */

  ret->type = type;
  ret->rotation = rotation;

  _logf(L_INFO, "Boat constructed at (%d, %d) with type %d and rotation %d", x, y, type, rotation);
  return ret;
}

void destruct_boat(Boat* boat)
{
  _logf(L_INFO, "Boat destructed with type %hhu and rotation %hhu", boat->type, boat->rotation);
  free(boat);
  return;
}
