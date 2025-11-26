#ifndef LOGS_H
#define LOGS_H

#include "globals.h"
#include <stdio.h>

typedef enum
{
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

typedef enum
{
    LogSuccessFul = 0,
    LogFailure,
    FileDescriptorError,
} LogStatus;
typedef struct
{
    char msg[BUF_LEN_M];
    LogStatus code;
} LogError;

void message_logger(FILE *fp, LogLevel level, const char *message);
void init_logger(const char *file_path, FILE **fp);
void clean_up_logging(FILE **log_path);
#endif
