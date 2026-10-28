#include "global.h"
#include "logger/logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

PkgMeta *parse_meta(const char *meta_path) {
  FILE *file = fopen(meta_path, "r");
  if (!file) {
    return NULL;
  }

  PkgMeta *meta = calloc(1, sizeof(PkgMeta));
  if (!meta) {
    log_message(LOG_LEVEL_FATAL, "Couldn't alloc PkgMeta *meta !");
    fclose(file);
    return NULL;
  }

  char line[512];
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = '\0';
    if (line[0] == '\0' || line[0] == '#') {
      continue;
    }
    char *dlim = strchr(line, '=');
    if (!dlim) {
      continue;
    }
    *dlim = '\0';
    char *key = line;
    char *val = dlim+1;

    if (strcmp(key, "PKG_NAME")==0) {
      meta->name = strdup(val);
    } else if (strcmp(key, "PKG_PRETTY")==0) {
      meta->pretty = strdup(val);
    } else if (strcmp(key, "PKG_DESC")==0) {
      meta->desc = strdup(val);
    } else if (strcmp(key, "PKG_VER")==0) {
      meta->ver = strdup(val);
    } else if (strcmp(key, "PKG_CHKSUM")==0) {
      meta->chksum = strdup(val);
    }
  }
  fclose(file);
  return meta;
}

void free_meta(PkgMeta *meta) {
  if (!meta) return;
  free(meta->name);
  free(meta->pretty);
  free(meta->desc);
  free(meta->ver);
  free(meta->chksum);
  free(meta);
}

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
	PkgMeta *meta = parse_meta(found_path);
	if (meta) {
	  log_message(LOG_LEVEL_INFO, "%s (%s) - %s", meta->pretty ? meta->pretty : meta->name, meta->ver ? meta->ver : "Unknown", meta->desc ? meta->desc : "No description.");
	  free_meta(meta);
	}
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
      log_message(LOG_LEVEL_ERROR, "Couldn't find package: '%s'", pkg_name);
      fail_ctr++;
      continue;
    }
    log_message(LOG_LEVEL_DEBUG, "Meta location '%s'", meta_path);
  }
  if (fail_ctr > 0) {
    return 1;
  } else {
    log_message(LOG_LEVEL_INFO, "Install? [y/N]?");
    char resp = getchar();
    if (resp != 'y' && resp != 'Y') {
      log_message(LOG_LEVEL_ERROR, "Install aborted.");
    }
  }
  return 0;
}
