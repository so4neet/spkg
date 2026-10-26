#include <stdio.h>
#include "logger/logger.h"

int main(int argc, char *argv[]) {
  //if (argc > 1) {
    //for (int i=0; i<argc; i++) {
      
      // }
    // } else {
    //
    //  }
  //  return 0;
  log_message(LOG_LEVEL_FATAL, "This is a fatal error message.");
  log_message(LOG_LEVEL_ERROR, "This is an error message.");
  log_message(LOG_LEVEL_WARN, "This is a warning message.");
  log_message(LOG_LEVEL_INFO, "This is an informational message.");
  log_message(LOG_LEVEL_DEBUG, "This is a debug message.");
  return 0;
}
