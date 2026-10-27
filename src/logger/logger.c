#include "../global.h"
#include <stdio.h>
#include <stdarg.h>

static void print_log(log_level level, const char* msg, va_list args) {
  const char* lvl_clr[5] = {"0;41", "1;31", "1;33", "1;32", "1;34"};
  const char* lvl_str[5] = {"[ !! ] ", "[ !! ] ", "[ !! ] ", "[ :: ] ", "[ DD ] "};
  char buffer[4096];
  vsnprintf(buffer, sizeof(buffer), msg, args);

  #ifdef DEBUG
  if (level == LOG_LEVEL_DEBUG) {
    printf("\033[%sm%s\033[0m%s\n", lvl_clr[level], lvl_str[level], buffer);
  }
  #endif
  if (level != LOG_LEVEL_DEBUG && level < 5) {
    printf("\033[%sm%s\033[0m%s\n", lvl_clr[level], lvl_str[level], buffer);
  }
}

void log_message(log_level level, const char* msg, ...) {
  va_list args;
  va_start(args, msg);
  print_log(level, msg, args);
  va_end(args);
}
