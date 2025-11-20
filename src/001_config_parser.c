#include <stdio.h>
#include <yaml.h>
#include "include/config_parser.h"

size_t min(size_t a, size_t b) {
  return (a > b) * a + (a <= b) * b;
}

void print_app_config(AppConfig_t *cfg) {
  if (!cfg) return;
  puts("db:");
  printf("\t incremental_enabled: %li\n", cfg->db.incremental_enabled);
  printf("\t timeout_seconds: %li\n", cfg->db.timeout_seconds);
  printf("\t type: %s\n", cfg->db.type);
  printf("\t uri: %s\n", cfg->db.uri);

  puts("runtime:");
  printf("\t log_level: %li\n", cfg->runtime.log_level);
  printf("\t tmp_dir: %s\n", cfg->runtime.temp_dir);
  printf("\t thread_count: %li\n", cfg->runtime.thread_count);

  puts("storage:");
  printf("\t compression: %s\n", cfg->storage.compression);
  printf("\t key_path: %s\n", cfg->storage.encryption_key_path);
  printf("\t output_path: %s\n", cfg->storage.output_path);
  printf("\t remote_target: %s\n", cfg->storage.remote_target);
}

size_t assign_value(config_section_t section, const char *key,
  const char *value, AppConfig_t *cfg, ConfigParserError_t *err) {
  long val;

  if (section == SECTION_DB) {
    if (strcmp(key, "type") == 0) strncpy(cfg->db.type, value, BUF_LEN_XS);
    else if (strcmp(key, "uri") == 0) strncpy(cfg->db.uri, value, BUF_LEN_S);
    else if (strcmp(key, "timeout_seconds") == 0) {
      val = strtol(value, NULL, 10);

      if (val <= 0) {
        err->code = CONFIG_VALIDATION_ERROR;
        snprintf(err->message, sizeof(err->message), "db.timeout_seconds must be > 0");

        return -1;
      }

      cfg->db.timeout_seconds = (int)val;
    } else {
      err->code = CONFIG_VALIDATION_ERROR;
      snprintf(err->message, sizeof(err->message), "Unknown db key: %s", key);

      return -1;
    }
  } else if (section == SECTION_STORAGE) {
    if (strcmp(key, "output_path") == 0) strncpy(cfg->storage.output_path, value, BUF_LEN_S);
    else if (strcmp(key, "compression") == 0) strncpy(cfg->storage.compression, value, BUF_LEN_XS);
    else if (strcmp(key, "encryption_key_path") == 0) strncpy(cfg->storage.encryption_key_path, value, BUF_LEN_S);
    else {
      err->code = CONFIG_VALIDATION_ERROR;
      snprintf(err->message, sizeof(err->message), "Unknown storage key: %s", key);

      return -1;
    }
  } else if (section == SECTION_RUNTIME) {
    if (strcmp(key, "log_level") == 0) {
      val = strtol(value, NULL, 10);
      cfg->runtime.log_level = (int)val;
    } else if (strcmp(key, "thread_count") == 0) {
      val = strtol(value, NULL, 10);
      cfg->runtime.thread_count = (int)val;
    } else {
      err->code = CONFIG_VALIDATION_ERROR;
      snprintf(err->message, sizeof(err->message), "Unknown runtime key: %s", key);

      return -1;
    }
  }
  return 0;
}

ParserStatus_t config_load_file(const char *path, AppConfig_t *out_config, ConfigParserError_t **err) {
  FILE *fh = fopen(path, "r");
  yaml_parser_t parser;
  yaml_event_t event;
  ParserStatus_t status = CONFIG_OK;
  size_t status_text_cap = BUF_LEN_S;
  char *status_text = malloc(status_text_cap);
  ConfigParserError_t *local_err = create_parser_error();
  config_section_t current_section = SECTION_NONE;
  parse_phase_t phase = EXPECT_KEY;
  char current_key[BUF_LEN_S] = {0};
  _Bool done = false;

  if (!local_err) {
    fclose(fh);

    return status;
  }

  if (!status_text) {
    status = CONFIG_MEMORY_ERROR;
    local_err->code = status;
    snprintf(local_err->message, sizeof(local_err->message), "Config parse error: %s", "Failed to initialize status text!");
    *err = local_err;

    return status;
  }

  if (!fh) {
    status = CONFIG_FILE_NOT_FOUND;
    local_err->code = status;
    snprintf(local_err->message, sizeof(local_err->message), "Config parse error: %s", "Config file not found!");
    *err = local_err;

    return status;
  }

  if (!yaml_parser_initialize(&parser)) {
    fclose(fh);
    status = CONFIG_MEMORY_ERROR;
    local_err->code = status;
    snprintf(local_err->message, sizeof(local_err->message), "Config parse error: %s", "Failed to initialize parser!");
    *err = local_err;

    return status;
  }

  yaml_parser_set_input_file(&parser, fh);

  if (!out_config) {
    yaml_parser_delete(&parser);
    fclose(fh);
    status = CONFIG_MEMORY_ERROR;
    local_err->code = status;
    snprintf(local_err->message, sizeof(local_err->message), "Config parse error: %s", "No/invalid output config struct!");
    *err = local_err;

    return status;
  }

  while (!done) {
    if (!yaml_parser_parse(&parser, &event)) {
      if (err) {
        status = CONFIG_PARSE_ERROR;

        local_err->code = status;
        snprintf(status_text, status_text_cap, "YAML parse error: %s", parser.problem);
        local_err->line = parser.problem_mark.line + 1;
        local_err->column = parser.problem_mark.column + 1;
      }

      yaml_parser_delete(&parser);
      fclose(fh);

      break;
    }

    switch (event.type) {
      case YAML_SCALAR_EVENT:
        if (phase == EXPECT_KEY) {
          strncpy(current_key, (char*)event.data.scalar.value, BUF_LEN_S);
          phase = EXPECT_VALUE;
        } else {
          if (assign_value(current_section, current_key, (char*)event.data.scalar.value, out_config, local_err) != 0) {
            yaml_event_delete(&event);
            yaml_parser_delete(&parser);
            fclose(fh);

            return local_err->code;
          }
          phase = EXPECT_KEY;
        }
      break;

      case YAML_MAPPING_START_EVENT:
        if (phase == EXPECT_VALUE) {
          phase = EXPECT_KEY;
          if (strcmp(current_key, "db") == 0) current_section = SECTION_DB;
          else if (strcmp(current_key, "storage") == 0) current_section = SECTION_STORAGE;
          else if (strcmp(current_key, "runtime") == 0) current_section = SECTION_RUNTIME;
          else current_section = SECTION_NONE;
          continue;
        }
        break;


      case YAML_MAPPING_END_EVENT:
        current_section = SECTION_NONE;
        break;

      case YAML_STREAM_END_EVENT:
        done = 1;
        break;

      default:
        break;
    }

    yaml_event_delete(&event);
  }

  if (status == CONFIG_OK) {
    destroy_parser_error(local_err);
    if (status_text) free(status_text);
  } else {
    snprintf(local_err->message, min(sizeof(local_err->message), status_text_cap), "%s", status_text);
    if (status_text) free(status_text);
    *err = local_err;
  }

  yaml_parser_delete(&parser);
  fclose(fh);

  return status;
}
