#include <stdio.h>
#include <string.h>

static unsigned int calc_sum(const char* input, size_t input_len, size_t offset)
{
    unsigned int sum = 0u;
    for (size_t i = 0u; i < input_len; ++i) 
    {
        if (input[i] == input[(i + offset) % input_len]) 
        {
            sum += input[i] - '0';
        }
    }

    return sum;
}

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    const char*  input     = argv[1];
    const size_t input_len = strlen(input);
    printf("Part1 = %i\n", calc_sum(input, input_len, 1));
    printf("Part2 = %i\n", calc_sum(input, input_len, input_len / 2));
    return 0;
}

