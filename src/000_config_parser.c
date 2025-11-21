#include "include/config_parser.h"


DBConfig_t *init_db_config(const char *type, const char *uri, size_t timeout_seconds, size_t incremental_enabled) {
  DBConfig_t *cfg = malloc(sizeof(DBConfig_t));

  if (!cfg) return NULL;
  strncpy(cfg->type, type, sizeof(cfg->type) - 1);
  cfg->type[sizeof(cfg->type) - 1] = '\0';
  strncpy(cfg->uri, uri, sizeof(cfg->uri) - 1);
  cfg->uri[sizeof(cfg->uri) - 1] = '\0';
  cfg->timeout_seconds = timeout_seconds;
  cfg->incremental_enabled = incremental_enabled;

  return cfg;
}

StorageConfig_t *init_storage_config(const char *output_path, const char *compression, const char *encryption_key_path, const char *remote_target) {
  StorageConfig_t *cfg = malloc(sizeof(StorageConfig_t));

  if (!cfg) return NULL;
  strncpy(cfg->output_path, output_path, sizeof(cfg->output_path) - 1);
  cfg->output_path[sizeof(cfg->output_path) - 1] = '\0';
  strncpy(cfg->compression, compression, sizeof(cfg->compression) - 1);
  cfg->compression[sizeof(cfg->compression) - 1] = '\0';
  strncpy(cfg->encryption_key_path, encryption_key_path, sizeof(cfg->encryption_key_path) - 1);
  cfg->encryption_key_path[sizeof(cfg->encryption_key_path) - 1] = '\0';
  strncpy(cfg->remote_target, remote_target, sizeof(cfg->remote_target) - 1);
  cfg->remote_target[sizeof(cfg->remote_target) - 1] = '\0';

  return cfg;
}

RuntimeConfig_t *init_runtime_config(size_t log_level, size_t thread_count, const char *temp_dir) {
  RuntimeConfig_t *cfg = malloc(sizeof(RuntimeConfig_t));

  if (!cfg) return NULL;
  cfg->log_level = log_level;
  cfg->thread_count = thread_count;
  strncpy(cfg->temp_dir, temp_dir, sizeof(cfg->temp_dir) - 1);
  cfg->temp_dir[sizeof(cfg->temp_dir) - 1] = '\0';

  return cfg;
}

AppConfig_t *init_app_config(DBConfig_t *db, StorageConfig_t *storage, RuntimeConfig_t *runtime) {
  AppConfig_t *cfg = malloc(sizeof(AppConfig_t));

  if (!cfg) return NULL;
  cfg->db = *db;
  cfg->storage = *storage;
  cfg->runtime = *runtime;

  return cfg;
}

ConfigParserError_t *create_parser_error() {
  ConfigParserError_t *err = malloc(sizeof(ConfigParserError_t));
  err->code = CONFIG_OK;
  err->line = 0;
  err->column = 0;

  return err;
}

void destroy_db_config(DBConfig_t **cfg) {
  if (!cfg) return;
  if (!*cfg) {
    free(cfg);
    return;
  }

  free(*cfg);
  *cfg = NULL;
}

void destroy_runtime_config(RuntimeConfig_t **cfg) {
  if (!cfg) return;
  if (!*cfg) {
    free(cfg);
    return;
  }

  free(*cfg);
  *cfg = NULL;
}

void destroy_storage_config(StorageConfig_t **cfg) {
  if (!cfg) return;
  if (!*cfg) {
    free(cfg);
    return;
  }

  free(*cfg);
  *cfg = NULL;
}

void destroy_app_config(AppConfig_t **cfg) {
  if (!cfg) return;
  if (!*cfg) {
    free(cfg);
    return;
  }

  free(*cfg);
  *cfg = NULL;
}

void destroy_parser_error(ConfigParserError_t **err) {
  if (!err) return;
  if (!*err) {
    free(err);

    return;
  }

  free(*err);
  *err = NULL;
}
