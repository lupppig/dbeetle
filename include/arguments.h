#ifndef ARGUMENTS_H
#define ARGUMENTS_H
#include <stdbool.h>

typedef enum
{
    ARG_TYPE_BOOL,
    ARG_TYPE_INT,
    ARG_TYPE_STRING,
} ArgType;

typedef enum
{
    ARG_POSITIONAL,
    ARG_SHORT_FLAG,
    ARG_LONG_FLAG,
} Flag;

typedef struct
{
    char *name;
    Flag flag;
    ArgType type;
    const char *description;
    void *value;
    bool required;
} Arguments;

typedef struct
{
    Arguments *args;
    int arg_counts;
    int capacity;
} ArgParser;

// argument option regsitry
typedef struct
{
    const char *db;
    const char *dbtype;
    const char *host;
    int port;
    const char *password;
    const char *user;
    const char *db_uri;
} Options;

#endif