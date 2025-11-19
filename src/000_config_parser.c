#include "include/config_parser.h"

DBConfig_t *init_DBConfig(const char *type, const char *uri, int timeout_seconds, int incremental_enabled) {
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

StorageConfig_t *init_StorageConfig(const char *output_path, const char *compression, const char *encryption_key_path, const char *remote_target) {
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

RuntimeConfig_t *init_RuntimeConfig(int log_level, int thread_count, const char *temp_dir) {
  RuntimeConfig_t *cfg = malloc(sizeof(RuntimeConfig_t));

  if (!cfg) return NULL;
  cfg->log_level = log_level;
  cfg->thread_count = thread_count;
  strncpy(cfg->temp_dir, temp_dir, sizeof(cfg->temp_dir) - 1);
  cfg->temp_dir[sizeof(cfg->temp_dir) - 1] = '\0';

  return cfg;
}

AppConfig_t *init_AppConfig(DBConfig_t *db, StorageConfig_t *storage, RuntimeConfig_t *runtime) {
  AppConfig_t *cfg = malloc(sizeof(AppConfig_t));

  if (!cfg) return NULL;
  cfg->db = db;
  cfg->storage = storage;
  cfg->runtime = runtime;

  return cfg;
}
