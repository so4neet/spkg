#include <string.h>
#include "logger/logger.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "install")==0) { log_message(LOG_LEVEL_INFO, "Install function"); };
    }
  return 0;
}
