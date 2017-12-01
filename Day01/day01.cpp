#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::strlen;

static unsigned int calc_sum(const char* input,
                             size_t      input_len,
                             size_t      offset)
{
    unsigned int sum = 0u;

    for (auto i = 0u; i < input_len; ++i)
    {
        if (input[i] == input[(i + offset) % input_len])
        {
            sum += static_cast<unsigned int>(input[i] - '0');
        }
    }

    return sum;
}

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        cout << "Invalid arguments!\n";
        return 1;
    }

    const char*  input     = argv[1];
    const size_t input_len = strlen(input);

    cout << "(Part 1) Sum = " << calc_sum(input, input_len, 1) << endl;
    cout << "(Part 2) Sum = " << calc_sum(input, input_len, input_len / 2) << endl;
    return 0;
}

