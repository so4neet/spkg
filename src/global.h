#pragma once

typedef enum {
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR = 1,
  LOG_LEVEL_WARN  = 2,
  LOG_LEVEL_INFO  = 3,
  LOG_LEVEL_DEBUG = 4
} log_level;

#define SPKG_PATH "/opt/spkg/"
#define SPKG_CACHE "/opt/spkg/cache/"
#define SPKG_PKGS "/opt/spkg/installed/"
