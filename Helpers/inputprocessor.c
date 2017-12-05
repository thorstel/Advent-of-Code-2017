#include <ctype.h>

#include "inputprocessor.h"

static char buffer[256];
static const size_t buffer_size = sizeof(buffer);

bool process_input(FILE* input, bool (*process)(char*, size_t, bool))
{
    if ((input == NULL) || (process == NULL)) 
    {
        return false;
    }

    int    c;
    size_t i = 0;

    while (((c = getc(input)) != EOF) && (i < buffer_size))
    {
        if ((isprint(c)) && (!isspace(c)))
        {
            buffer[i++] = (char)c;
        }
        else
        {
            buffer[i] = '\0';
            if (!process(buffer, i, ((char)c == '\n'))) { return false; }
            i = 0;
        }
    }

    return (i < buffer_size);
}

