#include <stdio.h>
#include "include/config_parser.h"  // your header for AppConfig_t, config_load_file, etc.

/**
  * -------------------AI-GENERATED CODE----------------------
*/

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <config.yml>\n", argv[0]);
        return 1;
    }

    const char *config_path = argv[1];

    DBConfig_t *cfg_db = init_db_config("passed:postgres", "passed:https://db", 5000, 1);
    StorageConfig_t *cfg_storage = init_storage_config("passed:./tests", "passed:shannon", "passed:./pat", "passed:http://remote");
    RuntimeConfig_t *cfg_runtime = init_runtime_config(3, 2, "passed:locals");
    AppConfig_t *cfg = init_app_config(cfg_db, cfg_storage, cfg_runtime);

    ConfigParserError_t *err = NULL;

    ConfigParserStatus_t status = config_load_file(config_path, cfg, &err);

    if (status != CONFIG_OK) {
        if (err) {
          printf("Error [%d] line %li col %li: %s\n", err->code, err->line, err->column, err->message);
          destroy_parser_error(&err);
        } else {
          printf("An unknown error occurred when parsing the config\n");
        }

        destroy_app_config(&cfg);
        return 1;
    }

    // Simple verification of values
    print_app_config(cfg);



    // Clean up
    destroy_app_config(&cfg);


    printf("Config loader test passed.\n");
    return 0;
}
