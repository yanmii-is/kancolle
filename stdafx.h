#pragma once
#include <stdint.h>

typedef int8_t   s8;
typedef uint8_t  u8;
typedef int16_t  s16;
typedef uint16_t u16;

typedef enum {
  RETURN_OK                 = 0x0000,
  GAME_INVALID_GAME         = 0xA001,
  GAME_INVALID_PLAYER       = 0xA002,
  GAME_INVALID_BOARD        = 0xA003,
  GAME_INVALID_COORDINATES  = 0xA004,
  GAME_ATTACK_HIT_SEA       = 0xA005,
  GAME_ATTACK_HIT_BOAT      = 0xA006,
  GAME_ATTACK_ALREADY_HIT   = 0xA007,
  BOARD_INVALID_BOARD       = 0xB001,
  BOARD_INVALID_BOAT        = 0xB002,
  BOARD_INVALID_COORDINATES = 0xB003,
  BOARD_ADD_OVERLAP         = 0xB004,
  BOAT_INVALID_BOAT         = 0xC001
} return_code;
