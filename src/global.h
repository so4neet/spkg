#pragma once

typedef enum {
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR = 1,
  LOG_LEVEL_WARN  = 2,
  LOG_LEVEL_INFO  = 3,
  LOG_LEVEL_DEBUG = 4
} log_level;

typedef struct {
  unsigned int SPKG_MODE_SYNC : 1;
  unsigned int SPKG_MODE_UPDATE : 1;
  unsigned int SPKG_MODE_SEARCH : 1;
  unsigned int SPKG_MODE_REMOVE : 1;
  unsigned int SPKG_MODE_INSTALL : 1;
  unsigned int SPKG_MODE_ROLLBACK : 1;
  unsigned int SPKG_MODE_SHOW_VER : 1;
  unsigned int SPKG_MODE_SHOW_HELP : 1;
} spkg_opts;

typedef struct {
  char *name;
  char *pretty;
  char *desc;
  char *ver;
  char *chksum;
} PkgMeta;

#define SPKG_PATH "/opt/spkg"
#define SPKG_CACHE "/opt/spkg/cache"
#define SPKG_PKGS "/opt/spkg/installed"
#define SPKG_REPO "/opt/spkg/repo"
