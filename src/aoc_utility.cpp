#include "aoc_utility.hpp"
#include "default_includes.hpp"

/**********************************************************************
 *                             Knot Hash                              *
 **********************************************************************/

std::array<unsigned int, 16> aoc::knot_hash(const std::string& input)
{
    static std::array<unsigned int, 256> array;
    std::iota(array.begin(), array.end(), 0u);

    std::vector<unsigned int> inputs;
    std::for_each(input.begin(), input.end(),
            [&](auto c) {
                inputs.push_back(static_cast<unsigned int>(c));
            });
    for (auto i : {17u, 31u, 73u, 47u, 23u}) { inputs.push_back(i); }

    unsigned int pos{0u}, skip{0u};
    for (auto i{0}; i < 64; ++i) { knot_hash_round(array, inputs, pos, skip); }

    std::array<unsigned int, 16> hash;
    auto hh = hash.begin();
    for (auto it = array.begin(); it != array.end(); std::advance(it, 16))
    {
        *(hh++) = std::accumulate(it, (it + 16), 0u, std::bit_xor<void>());
    }

    return hash;
}

void aoc::knot_hash_round(
        std::array<unsigned int, 256>&   array,
        const std::vector<unsigned int>& inputs,
        unsigned int&                    pos,
        unsigned int&                    skip)
{
    for (auto len : inputs)
    {
        unsigned int start_pos{pos};
        unsigned int end_pos = ((pos + len) - 1u) % array.size();

        for (auto i{0u}; i < (len / 2u); ++i)
        {
            std::swap(array[start_pos], array[end_pos]);
            start_pos = (start_pos + 1u) % array.size();
            end_pos   = (end_pos > 0u) ? (end_pos - 1u) : (array.size() - 1u);
        }

        pos = (pos + (len + skip++)) % array.size();
    }
}

