#ifndef ___CONFIG_PARSER_H___
#define ___CONFIG_PARSER_H___

// external library headers
#include <yaml.h>

// standard library headers
#include <stdbool.h>

//internal library headers

//macro defs
#define BUF_LEN_XS (64)
#define BUF_LEN_S (256)
#define BUF_LEN_M (512)
#define BUF_LEN (1024)


typedef struct DBConfig {
  char             type[BUF_LEN_XS];
  char             uri[BUF_LEN_S];
  size_t           timeout_seconds;
  size_t           incremental_enabled;
} DBConfig_t;

typedef enum {
  SECTION_NONE,
  SECTION_DB,
  SECTION_STORAGE,
  SECTION_RUNTIME
} config_section_t;

typedef enum {
  EXPECT_KEY,
  EXPECT_VALUE
} parse_phase_t;

typedef struct storageConfig {
  char          output_path[BUF_LEN_S];
  char          compression[BUF_LEN_XS];
  char          encryption_key_path[BUF_LEN_S];
  char          remote_target[BUF_LEN_S];
} StorageConfig_t;

typedef struct RuntimeConfig {
  size_t          log_level;
  size_t          thread_count;
  char            temp_dir[BUF_LEN_S];
} RuntimeConfig_t;

typedef struct AppConfig {
  DBConfig_t           db;
  StorageConfig_t      storage;
  RuntimeConfig_t      runtime;
} AppConfig_t;

typedef enum {
  CONFIG_OK = 0,
  CONFIG_FILE_NOT_FOUND,
  CONFIG_PARSE_ERROR,
  CONFIG_VALIDATION_ERROR,
  CONFIG_MEMORY_ERROR
} ParserStatus_t;

typedef struct ConfigParserError {
  ParserStatus_t        code;
  char                  message[BUF_LEN_M];
  size_t                line;
  size_t                column;
} ConfigParserError_t;


/**
 * config_load_file - loads config file
 * @path: location of config file
 * @out_config: the output config options in a defined struct
 * @err: written error object on failure
 *
 * Return: ParserStatus_t
 * ~NOTE~:
 **/
ParserStatus_t config_load_file(const char *path, AppConfig_t *out_config, ConfigParserError_t **err);

DBConfig_t *init_db_config(const char *type, const char *uri, size_t timeout_seconds, size_t incremental_enabled);

StorageConfig_t *init_storage_config(const char *output_path, const char *compression, const char *encryption_key_path, const char *remote_target);

RuntimeConfig_t *init_runtime_config(size_t log_level, size_t thread_count, const char *temp_dir);

AppConfig_t *init_app_config(DBConfig_t *db, StorageConfig_t *storage, RuntimeConfig_t *runtime);

ConfigParserError_t *create_parser_error();

void print_app_config(AppConfig_t *cfg);
void destroy_db_config(DBConfig_t *cfg);
void destroy_storage_config(StorageConfig_t *cfg);
void destroy_runtime_config(RuntimeConfig_t *cfg);
void destroy_app_config(AppConfig_t *cfg);
void destroy_parser_error(ConfigParserError_t *err);


#endif /* ___CONFIG_PARSER_H___ */
