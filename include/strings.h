#ifndef __STRINGS_H__
#define __STRINGS_H__

#include <stddef.h>
typedef struct
{
    char *buf;
    size_t len;
    size_t cap;
} StringBuilder;

StringBuilder *sb_init(void);
void sb_free(StringBuilder *sb);
const char *sb_data(const StringBuilder *sb);
void sb_append(StringBuilder *sb, const char *str);

#endif
