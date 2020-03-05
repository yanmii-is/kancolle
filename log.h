#include <stdio.h>
#include <stdarg.h>


typedef const enum {L_FATAL, L_ERROR, L_TODO, L_SUCCESS, L_WARNING, L_INFO, L_TRACE} level;

void _logf(level level, const char *fmt, ...);
