#pragma once

typedef struct {
  Boat*    boat;
  uint8_t  shot; // 0: NoShot, 1: NoHit, 2: Hit
} Cell;
