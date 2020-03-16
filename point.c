#include "point.h"


Point* construct_point(uint8_t x, uint8_t y)
{
  Point* ret = malloc(sizeof(Point));
  ret->x = x;
  ret->y = y;
  ret->display = false;
  _logf(L_INFO, "Point created at (%d, %d) with display %s", x, y, ret->display ? "true" : "false");
  return ret;
}

void destruct_point(Point* point)
{
  _logf(L_INFO, "Point destructed at (%d, %d)", point->x, point->y);
  free(point);
  return;
}
