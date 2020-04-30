#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "board.h"
#include "config.h"

typedef struct
{
	u8      state;
	Board*  board_p1;
	Board*  board_p2;
} Game;

Game*        game_construct  (u8 height, u8 width);
return_code  game_destruct   (Game* game);
return_code  game_print      (Game* game);
return_code  game_verify     (Game* game, u8 player);
return_code  game_attack     (Game* game, u8 player, u8 x, u8 y);
