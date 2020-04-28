#include "boat.h"

// Bitmap presets
u8 bitmap_TL1[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
u8 bitmap_TL2[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
u8 bitmap_TL3[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
u8 bitmap_TL4[5][5] = {
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 }
};
u8 bitmap_TT5[5][5] = {
  { 0, 0, 0, 0, 0 },
  { 0, 1, 1, 1, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0 }
};


Boat* boat_construct(BoatType type, BoatRotation rotation)
{
  Boat* ret;

  ret           = malloc(sizeof(Boat));
  ret->type     = type;
  ret->rotation = rotation;
  ret->damage   = 0;

  switch (type)
  {
    case TYPE_LINEAR_1:
      memcpy(&ret->bitmap, &bitmap_TL1, sizeof(u8) * 5 * 5);
      break;
    case TYPE_LINEAR_2:
      memcpy(&ret->bitmap, &bitmap_TL2, sizeof(u8) * 5 * 5);
      break;
    case TYPE_LINEAR_3:
      memcpy(&ret->bitmap, &bitmap_TL3, sizeof(u8) * 5 * 5);
      break;
    case TYPE_LINEAR_4:
      memcpy(&ret->bitmap, &bitmap_TL4, sizeof(u8) * 5 * 5);
      break;
    case TYPE_TSHAPE_5:
      memcpy(&ret->bitmap, &bitmap_TT5, sizeof(u8) * 5 * 5);
      break;
    default:
      _logf(L_FATAL, "Attempted construction boat with invalid or unsupported type %d", type);
  }

  _logf(L_INFO, "Boat constructed with type %d and rotation %d", type, rotation);
  return ret;
}

void boat_destruct(Boat* boat)
{
  _logf(L_INFO, "Boat destructed with type %d and rotation %d", boat->type, boat->rotation);
  free(boat);
  return;
}

void boat_print(Boat* boat)
{
  // Bitmap headers
  printf("   | ");
  for (u8 x = 0; x < 5; x++)
  {
    printf("%02hhu ", x);
  }
  printf("\n");

  printf("---+");
  for (u8 x = 0; x < 5; x++)
  {
    printf("---");
  }
  printf("\n");

  // Bitmap content
  for (u8 x = 0; x < 5; x++)
  {
    printf("%02hhu | ", x);
    for (u8 y = 0; y < 5; y++)
    {
      switch (boat->bitmap[x][y])
      {
        case 0:
          printf("~~ ");
          break;
        case 1:
          printf("BB ");
          break;
        case 2:
          printf("±± ");
          break;
        case 3:
          printf("xx ");
          break;
        default:
          printf("?? ");
      }
    }
    printf("\n");
  }
}

// Clockwise rotation (90º)
void boat_rotate(Boat* boat)
{
  u8 rotated[5][5];

  for (u8 i = 0; i < 5; i++)
  {
    for (u8 j = 0; j < 5; j++)
    {
      rotated[i][j] = boat->bitmap[5-j-1][i];
    }
  }

  memcpy(&boat->bitmap, &rotated, sizeof(u8) * 5 * 5);

  boat->rotation = (boat->rotation == 0) ? 3 : boat->rotation - 1;
}
