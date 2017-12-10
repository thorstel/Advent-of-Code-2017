#include <iostream>
#include <iterator>
#include <vector>

#include "solution.hpp"

template<>
void solve<Day05>(std::istream& ins, std::ostream& outs)
{
    std::vector<int> input    {std::istream_iterator<int>{ins}, {}};
    std::vector<int> input_p2 {input};

    auto calc_steps = [](std::vector<int>& input, bool is_part2) {
        int          pos   = 0;
        unsigned int steps = 0u;
        while ((pos >= 0) && (pos < static_cast<int>(input.size())))
        {
            if (is_part2 && (input[pos] > 2)) { pos += input[pos]--; }
            else                              { pos += input[pos]++; }
            ++steps;
        }

        return steps;
    };

    outs << "(Part 1) Steps = " << calc_steps(input, false) << std::endl
         << "(Part 2) Steps = " << calc_steps(input_p2, true) << std::endl;
}

