#include "boat.h"

// Bitmap presets
uint8_t bitmap_TL1[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
uint8_t bitmap_TL2[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 },
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


Boat* construct_boat(BoatType type, BoatRotation rotation)
{
  Boat* ret = malloc(sizeof(Boat));

  ret->type = type;
  ret->rotation = rotation;

  switch (type)
  {
    case TYPE_LINEAR_1:
      memcpy(bitmap_TL1, ret->bitmap, sizeof(uint8_t) * 5 * 5);
      break;
    case TYPE_LINEAR_2:
      memcpy(bitmap_TL2, ret->bitmap, sizeof(uint8_t) * 5 * 5);
      break;
    case TYPE_LINEAR_3:
      memcpy(bitmap_TL3, ret->bitmap, sizeof(uint8_t) * 5 * 5);
      break;
    case TYPE_LINEAR_4:
      memcpy(bitmap_TL4, ret->bitmap, sizeof(uint8_t) * 5 * 5);
      break;
    case TYPE_TSHAPE_5:
      memcpy(bitmap_TT5, ret->bitmap, sizeof(uint8_t) * 5 * 5);
      break;
    default:
      _logf(L_FATAL, "Attempted construction boat with invalid or unsupported type %d", type);
  }

  _logf(L_INFO, "Boat constructed with type %d and rotation %d", type, rotation);
  return ret;
}

void destruct_boat(Boat* boat)
{
  _logf(L_INFO, "Boat destructed with type %hhu and rotation %hhu", boat->type, boat->rotation);
  free(boat);
  return;
}
