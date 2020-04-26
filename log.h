#pragma once
#include <stdio.h>
#include <stdarg.h>
#include "config.h"

typedef const enum {L_FATAL, L_ERROR, L_TODO, L_SUCCESS, L_WARNING, L_INFO, L_TRACE} Level;

void _logf  (Level level, const char *fmt, ...);
