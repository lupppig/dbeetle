#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "include/logs.h"
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "include/strings.h"

#define BUF_LEVEL 6
void init_logger(const char *file_path, FILE **fp)
{
    if (!file_path || file_path[0] == '\0')
        *fp = stdout;

    *fp = fopen(file_path, "a+");
    if (!fp)
        *fp = stdout;
}

void clean_up_logging(FILE **log_path)
{
    if (log_path && *log_path && *log_path != stdout)
    {
        fclose(*log_path);
        *log_path = NULL;
    }
}

void message_logger(FILE *fp, LogLevel level, const char *message)
{
    if (!fp || !message)
        return;

    char *str_level;
    switch (level)
    {
    case LOG_INFO:
        str_level = "INFO";
        break;
    case LOG_WARN:
        str_level = "WARN";
        break;
    case LOG_ERROR:
        str_level = "ERROR";
        break;
    default:
        return;
    }

    time_t now = time(NULL);
    struct tm *c_time = localtime(&now);

    fprintf(fp, "%04d-%02d-%02d %02d:%02d:%02d [%s] %s\n",
            c_time->tm_year + 1900,
            c_time->tm_mon + 1,
            c_time->tm_mday,
            c_time->tm_hour,
            c_time->tm_min,
            c_time->tm_sec,
            str_level,
            message);

    fflush(fp);
}
