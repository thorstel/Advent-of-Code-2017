#include "aoc_utility.hpp"
#include "default_includes.hpp"
#include "solution.hpp"

static constexpr int pos_key(int x, int y) { return (x << 8) | y; }

template<>
void solve<Day14>(std::istream& ins, std::ostream& outs)
{
    NOT_USED(ins);

    int                     num_used {0};
    std::string             input    {"ffayrhll"};
    aoc::disjoint_sets<int> regions;

    for (auto y {0}; y < 128; ++y)
    {
        std::ostringstream oss;
        oss << input << "-" << y;

        auto x {0};
        for (auto byte : aoc::knot_hash(oss.str()))
        {
            for (auto b {7}; b >= 0; --b, ++x)
            {
                if (byte & (1 << b))
                {
                    const auto region {regions.find(pos_key(x, y))};
                    const auto left   {pos_key((x - 1), y)};
                    const auto up     {pos_key(x, (y - 1))};
                    if ((x > 0) && regions.contains(left))
                    {
                        regions.make_union(region, left);
                    }
                    if ((y > 0) && regions.contains(up))
                    {
                        regions.make_union(region, up);
                    }

                    ++num_used;
                }
            }
        }
    }

    outs << "Used squares      = " << num_used << std::endl
         << "Number of regions = " << regions.set_count() << std::endl;
}

