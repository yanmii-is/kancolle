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
  ret->damage = 0;

  switch (type)
  {
    case TYPE_LINEAR_1:
      memcpy(&ret->bitmap, &bitmap_TL1, sizeof(uint8_t) * 5 * 5);
      break;
    case TYPE_LINEAR_2:
      memcpy(&ret->bitmap, &bitmap_TL2, sizeof(uint8_t) * 5 * 5);
      break;
    case TYPE_LINEAR_3:
      memcpy(&ret->bitmap, &bitmap_TL3, sizeof(uint8_t) * 5 * 5);
      break;
    case TYPE_LINEAR_4:
      memcpy(&ret->bitmap, &bitmap_TL4, sizeof(uint8_t) * 5 * 5);
      break;
    case TYPE_TSHAPE_5:
      memcpy(&ret->bitmap, &bitmap_TT5, sizeof(uint8_t) * 5 * 5);
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

void print_bitmap(Boat* boat)
{
  // Bitmap headers
  printf("   | ");
  for (uint8_t x = 0; x < 5; x++)
  {
    printf("%02hhu ", x);
  }
  printf("\n");

  printf("---+");
  for (uint8_t x = 0; x < 5; x++)
  {
    printf("---");
  }
  printf("\n");

  // Bitmap content
  for (int x = 0; x < 5; x++)
  {
    printf("%02hhu | ", x);
    for (int y = 0; y < 5; y++)
    {
      switch (boat->bitmap[x][y])
      {
        case 0:
          printf("~~ ");
          break;
        case 1:
          printf("XX ");
          break;
        default:
          printf("?? ");
      }
    }
    printf("\n");
  }
}

// Clockwise rotation (90º)
void rotate_boat(Boat* boat)
{
  uint8_t rotated[5][5];

  for (uint8_t i = 0; i < 5; i++)
  {
    for (uint8_t j = 0; j < 5; j++)
    {
      rotated[i][j] = boat->bitmap[5-j-1][i];
    }
  }

  memcpy(&boat->bitmap, &rotated, sizeof(uint8_t) * 5 * 5);

  boat->rotation = (boat->rotation == 0) ? 3 : boat->rotation - 1;
}
