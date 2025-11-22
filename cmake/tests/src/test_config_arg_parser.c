#include <stdbool.h>
#include "include/config_parser.h"

/* ____________________________ AI GENERATED _________________________ */

int main(int argc, char *argv[]) {
    // Step 1: Create schema
    AppConfig_t *cfg = merge_configs(argc, argv);
    print_app_config(cfg);
    destroy_app_config(&cfg);

    return 0;
}
