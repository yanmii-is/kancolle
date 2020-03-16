#include "log.h"


void _logf(Level level, const char *fmt, ...)
{
  // Check if logging is disabled
  if (!LOGGING)
  {
    return;
  }

  va_list args;

  switch (level)
  {
    case L_FATAL:
      fprintf(stderr, "[F] ");
      break;
    case L_ERROR:
      fprintf(stderr, "[E] ");
      break;
    case L_TODO:
      fprintf(stderr, "[U] ");
      break;
    case L_SUCCESS:
      fprintf(stderr, "[S] ");
      break;
    case L_WARNING:
      fprintf(stderr, "[W] ");
      break;
    case L_INFO:
      fprintf(stderr, "[!] ");
      break;
    case L_TRACE:
      fprintf(stderr, "[T] ");
      break;
    default:
      return;
  }

  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}
