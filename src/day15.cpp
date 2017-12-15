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

    uint64_t val1{input1};
    uint64_t val1_p2{input1};
    uint64_t val2{input2};
    uint64_t val2_p2{input2};
    size_t   matches{0u};
    size_t   matches_p2{0u};

    for (auto i = 0; i < 40000000; ++i)
    {
        val1 = gen_next<16807>(val1);
        val2 = gen_next<48271>(val2);
        if (is_match(val1, val2)) { ++matches; }

        if (i < 5000000)
        {
            val1_p2 = gen_next_p2<16807, 4>(val1_p2);
            val2_p2 = gen_next_p2<48271, 8>(val2_p2);
            if (is_match(val1_p2, val2_p2)) { ++matches_p2; }
        }
    }

    outs << "(Part 1) Number of matches = " << matches << std::endl
         << "(Part 2) Number of matches = " << matches_p2 << std::endl;
}

