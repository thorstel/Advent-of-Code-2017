#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "../Helpers/inputprocessor.h"

static int input[2048];
static size_t input_size = 0u;
static const size_t input_max_size = (sizeof(input) / sizeof(int));

static inline bool fill_array(char* s, size_t len, bool newline)
{
    (void)newline; /* unused */
    if (len != 0) { input[input_size++] = atoi(s); }
    return input_size < input_max_size;
}

/* call with argument '2' to execute part 2 */
int main(int argc, const char* argv[])
{
    FILE* fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        puts("Failed to open file!");
        return 1;
    }

    const bool input_succ = process_input(fp, fill_array);
    fclose(fp);
    if (!input_succ)
    {
        puts("Failed to process input!");
        return 1;
    }

    const bool   is_part2  = (argc > 1) && (argv[1][0] == '2');
    unsigned int step_ctr  = 0u;
    int          curr_pos  = 0;

    while ((curr_pos >= 0) && (curr_pos < (int)input_size))
    {
        int next_pos = curr_pos + input[curr_pos];

        if ((is_part2) && (input[curr_pos] > 2)) { --input[curr_pos]; }
        else                                     { ++input[curr_pos]; }

        ++step_ctr;
        curr_pos = next_pos;
    }

    printf("Steps = %u\n", step_ctr);
    return 0;
}

