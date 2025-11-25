#include <stdio.h>
#include <stdlib.h>
#include "include/strings.h"
#include <string.h>
#include "globals.h"

const char *sb_data(const StringBuilder *sb)
{
    return sb->buf ? sb->buf : "";
}

StringBuilder *sb_init(void)
{
    StringBuilder *sb = malloc(sizeof(StringBuilder));
    if (!sb)
        return NULL;

    sb->buf = malloc(BUF_LEN_XS);
    if (!sb->buf)
    {
        free(sb);
        return NULL;
    }

    sb->buf[0] = '\0';
    sb->cap = BUF_LEN_XS;
    sb->len = 0;

    return sb;
}

void sb_append(StringBuilder *sb, const char *str)
{
    size_t add = strlen(str);

    if (sb->len + add + 1 > sb->cap)
    {
        size_t new_cap = (sb->cap == 0 ? 64 : sb->cap * 2);
        while (new_cap < sb->len + add + 1)
            new_cap *= 2;

        char *tmp = realloc(sb->buf, new_cap);
        if (!tmp)
            return;

        sb->buf = tmp;
        sb->cap = new_cap;
    }

    memcpy(sb->buf + sb->len, str, add + 1);
    sb->len += add;
}

void sb_free(StringBuilder *sb)
{
    if (!sb)
        return;
    free(sb->buf);
    free(sb);
}