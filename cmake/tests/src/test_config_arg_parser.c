#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "include/arguments.h"

void add_flag(FlagSchemaEntry_t **schema, const char *key, ArgType type) {
  FlagSchemaEntry_t *entry = malloc(sizeof(FlagSchemaEntry_t));
  strncpy(entry->key, key, BUF_LEN_S);
  entry->type = type;
  HASH_ADD_STR(*schema, key, entry);
}

int main(int argc, char *argv[]) {
    // Step 1: Create schema
    FlagSchemaEntry_t *schema = NULL;
    add_flag(&schema, CFG_DB_PREFIX(type), ARG_TYPE_STRING);
    add_flag(&schema, CFG_DB_PREFIX(timeout_seconds), ARG_TYPE_INT);

    add_flag(&schema, CFG_STORAGE_PREFIX(compression), ARG_TYPE_STRING);
    add_flag(&schema, CFG_RUNTIME_PREFIX(log_level), ARG_TYPE_INT);
    // add_flag(&schema, "name", ARG_TYPE_STRING);

    // Step 2: Parsed arguments hash table
    Argument_t *parsed_args = NULL;
    ArgParserError_t *err = NULL;

    // Step 3: Parse the arguments
    ArgParserStatus_t status = parse_args(schema, &parsed_args, &err, argc, argv);

    if (status != ARG_SUCCESS) {
        if (err) {
            fprintf(stderr, "Error: %s\n", err->message);
            free(err);
        }
        destroy_flag_schema(schema);
        return 1;
    }

    // Step 4: Iterate over parsed arguments
    Argument_t *current, *tmp;
    HASH_ITER(hh, parsed_args, current, tmp) {
        printf("Parsed argument: %s = ", current->key);
        switch(current->type) {
            case ARG_TYPE_BOOL:
                printf("%s\n", *(bool *)current->value ? "true" : "false");
                break;
            case ARG_TYPE_INT:
                printf("%zu\n", *(size_t *)current->value);
                break;
            case ARG_TYPE_STRING:
                printf("%s\n", (char *)current->value);
                break;
        }
    }

    // Step 5: Cleanup
    destroy_parsed_argument(parsed_args);
    destroy_flag_schema(schema);

    return 0;
}
