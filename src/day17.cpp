#include <deque>

#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day17>(std::istream& ins, std::ostream& outs)
{
    NOT_USED(ins);

    const auto steps = 343; // input
    auto       pos   = 0;

    std::deque<int> buffer;
    buffer.emplace_back(0);
    for (auto i = 1; i <= 2017; ++i)
    {
        pos = ((pos + steps) % buffer.size()) + 1;
        buffer.emplace((buffer.begin() + pos), i);
    }

    outs << "(Part 1) Value after 2017 = " << buffer[pos + 1] << std::endl;

    auto value = 0;
    pos = 0;
    for (auto i = 1; i <= 50'000'000; ++i)
    {
        // 0 will remain at index 0, therefore we can just update the
        // value if insertion index is 1.
        if ((pos = ((pos + steps) % i) + 1) == 1) { value = i; }
    }

    outs << "(Part 2) Value after 0    = " << value << std::endl;
}

