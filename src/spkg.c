#include <string.h>
#include <unistd.h>
#include "version.h"
#include "logger/logger.h"
#include "install.h"

void print_help();

int main(int argc, char *argv[]) {
  int opt;
  spkg_opts pkg_opts = {0};
  
  while ((opt = getopt(argc, argv, "uUs:r:i:R:vh")) != -1) {
    switch (opt) {
    case 'u':
      pkg_opts.SPKG_MODE_SYNC = 1;
      break;
    case 'U':
      pkg_opts.SPKG_MODE_UPDATE = 1;
      break;
    case 's':
      pkg_opts.SPKG_MODE_SEARCH = 1;
      break;
    case 'r':
      pkg_opts.SPKG_MODE_REMOVE = 1;
      break;
    case 'i':
      pkg_opts.SPKG_MODE_INSTALL = 1;
      break;
    case 'R':
      pkg_opts.SPKG_MODE_ROLLBACK = 1;
      break;
    case 'v':
      pkg_opts.SPKG_MODE_SHOW_VER = 1;
      break;
    case 'h':
      pkg_opts.SPKG_MODE_SHOW_HELP = 1;
      break;
    default:
      log_message(LOG_LEVEL_ERROR, "Usage: 'spkg <parameters> <packages>'");
      return 1;
    }
  }
  if (pkg_opts.SPKG_MODE_SYNC) log_message(LOG_LEVEL_DEBUG, "Sync passed");
  if (pkg_opts.SPKG_MODE_UPDATE) log_message(LOG_LEVEL_DEBUG, "Update passed");
  if (pkg_opts.SPKG_MODE_SEARCH) log_message(LOG_LEVEL_DEBUG, "Search passed");
  if (pkg_opts.SPKG_MODE_REMOVE) log_message(LOG_LEVEL_DEBUG, "Remove passed");
  if (pkg_opts.SPKG_MODE_INSTALL) spkg_install(argc, argv);
  if (pkg_opts.SPKG_MODE_ROLLBACK) log_message(LOG_LEVEL_DEBUG, "Rollback passed");
  if (pkg_opts.SPKG_MODE_SHOW_VER) log_message(LOG_LEVEL_INFO, "spkg v:%s | Lira Devices", VERSION);
  if (pkg_opts.SPKG_MODE_SHOW_HELP) print_help();
  return 0;
}

void print_help() {
  log_message(LOG_LEVEL_INFO, "SPKG - Flags: ");
  log_message(LOG_LEVEL_INFO, "  -> 'i' | Install package(s) passed");
  log_message(LOG_LEVEL_INFO, "  -> 'U' | Update system");
  log_message(LOG_LEVEL_INFO, "  -> 'u' | Sync metadata");
  log_message(LOG_LEVEL_INFO, "  -> 'r' | Remove package(s) passed");
  log_message(LOG_LEVEL_INFO, "  -> 's' | Search for package(s) passed");
  log_message(LOG_LEVEL_INFO, "  -> 'R' | Rollback package passed to a specified version number. '*' can be passed to rollback the entire system to an earlier state if 'ROLLBACK_SYS_SNAPSHOTS=true' in '/opt/spkg/spkg.config'");
  log_message(LOG_LEVEL_INFO, "  -> 'v' | Shows version of SPKG");
  log_message(LOG_LEVEL_INFO, "  -> 'h' | Shows this message");
  log_message(LOG_LEVEL_INFO, "Flags can be chained together, so 'spkg -uUi nano' would sync metadata, update the system, then install 'nano'");
}
