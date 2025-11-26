#include "include/arguments.h"
#include <stdbool.h>
#include "include/logs.h"

int main(int argc, char **argv)
{
    FlagSchemaEntry_t *schema_head = NULL;

    add_flag(&schema_head, "log_path", ARG_TYPE_STRING);

    Argument_t *args;
    ArgParserError_t *err = NULL;
    parse_args(schema_head, &args, &err, argc, argv);

    if (err != NULL)
    {
        fprintf(stderr, "%s: %d", err->message, err->code);
        destroy_parsed_argument(args);
        destroy_flag_schema(schema_head);
        exit(EXIT_FAILURE);
    }

    if (args && args->key && args->value)
    {
        if (strcmp(args->key, "log_path") == 0)
        {
            FILE *fp;
            init_logger(args->value, &fp);
            message_logger(fp, LOG_INFO, "welcome to dbeetle...");
        }
    }

    return 0;
}
