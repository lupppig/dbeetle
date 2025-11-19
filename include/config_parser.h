#ifndef ___CONFIG_PARSER_H___
#define ___CONFIG_PARSER_H___

// external library headers
#include <yaml.h>

// standard library headers

//internal library headers


typedef struct DBConfig {
  char            type[16];
  char            uri[256];
  int             timeout_seconds;
  int             incremental_enabled;
} DBConfig_t;


typedef struct storageConfig {
  char          output_path[256];
  char          compression[32];
  char          encryption_key_path[256];
  char          remote_target[256];
} StorageConfig_t;

typedef struct RuntimeConfig {
  int         log_level;
  int         thread_count;
  char        temp_dir[256];
} RuntimeConfig_t;

typedef struct AppConfig {
  DBConfig_t           *db;
  StorageConfig_t      *storage;
  RuntimeConfig_t      *runtime;
} AppConfig_t;


#endif /* ___CONFIG_PARSER_H___ */
