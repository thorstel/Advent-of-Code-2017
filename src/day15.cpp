#include <future>

#include "aoc_utility.hpp"
#include "default_includes.hpp"
#include "solution.hpp"

static constexpr bool is_match(uint64_t x, uint64_t y)
{
    return (x & 0xFFFFu) == (y & 0xFFFFu);
}

template<>
void solve<Day15>(std::istream& ins, std::ostream& outs)
{
    NOT_USED(ins);

    const uint64_t input1 {289u}, input2 {629u};

    // Need the code duplication here so that the generator functions
    // are being inlined.
    auto exec_part1 = [] (uint64_t input1, uint64_t input2) -> size_t {
        size_t matches {0u};
        for (auto _ = 0; _ < 40'000'000; ++_)
        {
            input1 = aoc::generator_next<16807>(input1);
            input2 = aoc::generator_next<48271>(input2);
            if (is_match(input1, input2)) { ++matches; }
        }
        return matches;
    };
    auto exec_part2 = [] (uint64_t input1, uint64_t input2) -> size_t {
        size_t matches {0u};
        for (auto _ = 0; _ < 5'000'000; ++_)
        {
            input1 = aoc::generator_next<16807, 4>(input1);
            input2 = aoc::generator_next<48271, 8>(input2);
            if (is_match(input1, input2)) { ++matches; }
        }
        return matches;
    };

    auto result1 = std::async(std::launch::async, exec_part1, input1, input2);
    auto result2 = std::async(std::launch::async, exec_part2, input1, input2);

    outs << "(Part 1) Number of matches = " << result1.get() << std::endl
         << "(Part 2) Number of matches = " << result2.get() << std::endl;
}

