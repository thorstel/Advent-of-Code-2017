#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../Helpers/inputprocessor.h"

static inline int cmp_chars(const void* arg1, const void* arg2)
{
    const char c1 = *(const char*)arg1;
    const char c2 = *(const char*)arg2;

    if      (c1 < c2) { return -1; }
    else if (c1 > c2) { return  1; }
    else              { return  0; }
}

static inline bool reprint_words(char* str, size_t len, bool newline)
{
    if (len > 0)
    {
        qsort(str, len, sizeof(char), cmp_chars);
        printf("%s ", str);
    }

    if (newline) { putc('\n', stdout); }
    return true;
}

int main(void)
{
    if (!process_input(stdin, reprint_words))
    {
        puts("Failed to process input!");
        return 1;
    }

    return 0;
}

