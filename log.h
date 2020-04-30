#include <stdio.h>
#include <stdarg.h>
#include "config.h"

#ifndef LOG_H
#define LOG_H

typedef const enum {
	L_FATAL, L_ERROR, L_TODO, L_SUCCESS, L_WARNING, L_INFO, L_TRACE
} Level;

void _logf  (Level level, const char *fmt, ...);

#endif
