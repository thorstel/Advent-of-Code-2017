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
            [&] (auto c) { inputs.push_back(static_cast<unsigned int>(c)); });
    for (auto i : {17u, 31u, 73u, 47u, 23u}) { inputs.push_back(i); }

    unsigned int pos {0u}, skip {0u};
    for (auto _ = 0; _ < 64; ++_) { knot_hash_round(array, inputs, pos, skip); }

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
    const auto array_size = static_cast<unsigned int>(array.size());
    for (auto len : inputs)
    {
        unsigned int start_pos {pos},
                     end_pos   {((pos + len) - 1u) % array_size};
        for (auto _ = 0u; _ < (len / 2u); ++_)
        {
            std::swap(array[start_pos], array[end_pos]);
            start_pos = (start_pos + 1u) % array_size;
            end_pos   = (end_pos > 0u) ? (end_pos - 1u) : (array_size - 1u);
        }

        pos = (pos + (len + skip++)) % array_size;
    }
}

