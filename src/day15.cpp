#include <future>

#include "default_includes.hpp"
#include "solution.hpp"

template<uint64_t factor>
static constexpr uint64_t gen_next(uint64_t prev)
{
    return ((prev * factor) % 0x7FFFFFFFu);
}

template<uint64_t factor, uint64_t criteria>
static constexpr uint64_t gen_next_p2(uint64_t prev)
{
    uint64_t val = gen_next<factor>(prev);
    while ((val % criteria) != 0u) { val = gen_next<factor>(val); }
    return val;
}

static constexpr bool is_match(uint64_t x, uint64_t y)
{
    return (x & 0xFFFFu) == (y & 0xFFFFu);
}

template<>
void solve<Day15>(std::istream& ins, std::ostream& outs)
{
    NOT_USED(ins);

    const uint64_t input1{289u};
    const uint64_t input2{629u};

    // Need the code duplication here so that the generator functions
    // are being inlined.
    auto exec_part1 = [](uint64_t input1, uint64_t input2) -> size_t {
        size_t matches{0u};
        for (auto i = 0; i < 40000000; ++i)
        {
            input1 = gen_next<16807>(input1);
            input2 = gen_next<48271>(input2);
            if (is_match(input1, input2)) { ++matches; }
        }
        return matches;
    };
    auto exec_part2 = [](uint64_t input1, uint64_t input2) -> size_t {
        size_t matches{0u};
        for (auto i = 0; i < 5000000; ++i)
        {
            input1 = gen_next_p2<16807, 4>(input1);
            input2 = gen_next_p2<48271, 8>(input2);
            if (is_match(input1, input2)) { ++matches; }
        }
        return matches;
    };

    auto result1 = std::async(std::launch::async, exec_part1, input1, input2);
    auto result2 = std::async(std::launch::async, exec_part2, input1, input2);

    outs << "(Part 1) Number of matches = " << result1.get() << std::endl
         << "(Part 2) Number of matches = " << result2.get() << std::endl;
}

