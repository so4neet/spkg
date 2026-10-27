#include <string.h>
#include "logger/logger.h"
#include "install.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    if (strcmp(argv[1], "install")==0) { spkg_install(argc, argv); }
    if (strcmp(argv[1], "remove")==0) { log_message(LOG_LEVEL_INFO, "Remove function"); }
    if (strcmp(argv[1], "update")==0) { log_message(LOG_LEVEL_INFO, "Update function"); }
    if (strcmp(argv[1], "upgrade")==0) { log_message(LOG_LEVEL_INFO, "Upgrade function"); }
    if (strcmp(argv[1], "version")==0) { log_message(LOG_LEVEL_INFO, "Version function"); }
    if (strcmp(argv[1], "help")==0) { log_message(LOG_LEVEL_INFO, "Help function"); }
  } else {
    log_message(LOG_LEVEL_ERROR, "Please specify a flag, for help, append 'help'");
  }
  return 0;
}
