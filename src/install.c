#include "global.h"
#include "logger/logger.h"
#include <stdlib.h>
#include <string.h>

int spkg_install(int argc, char* argv[]) {
  if (argc <= 2) {
    log_message(LOG_LEVEL_ERROR, "Please specify a package to install");
    return 1;
  }
  
  size_t total_len = 0;
  for (int i=2; i < argc; i++) {
    total_len += strlen(argv[i])+2;
  }
  total_len += 1;
  char *vpkg_list = calloc(total_len, sizeof(char));
  if (vpkg_list == NULL) {
    log_message(LOG_LEVEL_FATAL, "Couldn't alloc memory for vpkg_list!");
    return 1;
  }
  vpkg_list[0] = '\0';
  for (int i=2; i < argc; i++) {
    strcat(vpkg_list, argv[i]);
    if (i < argc-1) {
      strcat(vpkg_list, ", ");
    }
  }
  log_message(LOG_LEVEL_INFO, "Installing packages %s...\n", vpkg_list);
  // actually fetch packages
  free(vpkg_list);
  return 0;
}
