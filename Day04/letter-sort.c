#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int cmp_chars(const void* arg1, const void* arg2)
{
    const char c1 = *(const char*)arg1;
    const char c2 = *(const char*)arg2;

    if      (c1 < c2) { return -1; }
    else if (c1 > c2) { return  1; }
    else              { return  0; }
}

int main(void)
{
    const size_t buf_size = 64;
    char         buf[buf_size];

    int    c;
    size_t i = 0;
    while (((c = getc(stdin)) != EOF) && (i < buf_size))
    {
        if (isalnum(c))
        {
            buf[i++] = (char)c;
        }
        else if (i > 0)
        {
            buf[i] = '\0';
            qsort(buf, i, sizeof(char), cmp_chars);
            printf("%s ", buf);
            i = 0;
        }
        else { /* ignore other characters */ }

        if ((char)c == '\n') { putc('\n', stdout); }
    }

    assert(i < buf_size);
    return 0;
}

