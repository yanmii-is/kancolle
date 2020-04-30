#pragma once
#include "stdafx.h"
#include "boat.h"

typedef struct {
  Boat* boat;
  u8    shot; // 0: NoShot, 1: NoHit, 2: Hit
} Cell;
