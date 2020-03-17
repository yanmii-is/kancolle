#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "log.h"


uint8_t read_u8(char *prompt);
bool read_bool(char *prompt);
void clear();
void newline();
