#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "log.h"
#include "utils.h"

typedef enum {
	ROTATION_0, ROTATION_90, ROTATION_180, ROTATION_270
} BoatRotation;

typedef enum {
	NONE, TYPE_LINEAR_1, TYPE_LINEAR_2, TYPE_LINEAR_3, TYPE_LINEAR_4, TYPE_TSHAPE_5
} BoatType;

extern u8 bitmap_TL1[5][5];
extern u8 bitmap_TL2[5][5];
extern u8 bitmap_TL3[5][5];
extern u8 bitmap_TL4[5][5];
extern u8 bitmap_TT5[5][5];

typedef struct
{
	BoatType      type;
	BoatRotation  rotation;
	u8            bitmap[5][5];  // 0: Empty, 1: NoHit, 2: Hit, 3: Miss
	u8            damage;
} Boat;

Boat*        boat_construct  (BoatType type, BoatRotation rotation);
return_code  boat_destruct   (Boat* boat);
return_code  boat_print      (Boat* boat);
return_code  boat_rotate     (Boat* boat);
