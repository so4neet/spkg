#include "global.h"
#include "logger/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char *locate_meta(const char *pkg_name) {
  DIR *dir = opendir(SPKG_REPO);
  if (!dir) {
    return NULL;
    log_message(LOG_LEVEL_DEBUG, "SPKG_REPO does not exist on rootfs !");
  }

  size_t target_len = strlen(pkg_name)+6;
  char *target_filename = calloc(target_len, sizeof(char));
  if (!target_filename) {
    closedir(dir);
    log_message(LOG_LEVEL_FATAL, "Couldn't alloc target_filename!");
    return NULL;
  }
  snprintf(target_filename, target_len, "%s.meta", pkg_name);

  char *found_path = NULL;
  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;    //Skip
    }

    if (strcmp(entry->d_name, target_filename) == 0) {
      size_t path_len = strlen(SPKG_REPO) + 1 + strlen(entry->d_name) + 1;
      found_path = calloc(path_len, sizeof(char));
      if (found_path) {
	snprintf(found_path, path_len, "%s/%s", SPKG_REPO, entry->d_name);
      }
      break;
    }
  }
  free(target_filename);
  closedir(dir);
  return found_path;
}


int spkg_install(int argc, char* argv[]) {
  if (argc <= 2) {
    log_message(LOG_LEVEL_ERROR, "Please specify a package to install");
    return 1;
  }
  
  int fail_ctr = 0;

  for (int i=2; i<argc; i++) {
    const char *pkg_name = argv[i];
    log_message(LOG_LEVEL_DEBUG, "Locating package meta for '%s'", pkg_name);
    char *meta_path = locate_meta(pkg_name);
    if (!meta_path) {
      log_message(LOG_LEVEL_DEBUG, "Meta does not exist for '%s'", pkg_name);
      fail_ctr++;
      continue;
    }
    log_message(LOG_LEVEL_DEBUG, "Meta location '%s'", meta_path);
    free(meta_path);
  }
  if (fail_ctr > 0) {
    log_message(LOG_LEVEL_ERROR, "Installation failed for %d package(s).", fail_ctr);
    return 1;
  }
  return 0;
}
