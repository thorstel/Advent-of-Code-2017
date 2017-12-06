#include <iostream>
#include <iterator>
#include <map>
#include <vector>

int main(void)
{
    std::vector<int> banks { std::istream_iterator<int> { std::cin }, {} };
    const auto bank_size = banks.size();

    auto max_pos = 0u;
    for (auto i = 0u; i < bank_size; ++i)
    {
        if (banks[max_pos] < banks[i]) { max_pos = i; }
    }

    std::map<std::vector<int>, size_t> known;
    for (size_t count = 0u; known.emplace(banks, count).second; ++count)
    {
        auto to_distribute = banks[max_pos];
        auto curr_pos      = (max_pos + 1) % bank_size;
        banks[max_pos]     = 0;

        while (to_distribute > 0)
        {
            ++banks[curr_pos];
            if ((banks[curr_pos] > banks[max_pos]) ||
                ((banks[curr_pos] == banks[max_pos]) && (curr_pos < max_pos)))
            {
                max_pos = curr_pos;
            }

            curr_pos = (curr_pos + 1) % bank_size;
            --to_distribute;
        }
    }

    std::cout << "Redistributions = " << known.size() << std::endl;
    std::cout << "Cycles = " << (known.size() - known[banks]) << std::endl;
    return 0;
}

