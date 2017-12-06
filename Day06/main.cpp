#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

int main(void)
{
    std::vector<int> banks { std::istream_iterator<int> { std::cin }, {} };
    std::map<std::vector<int>, size_t> known;

    for (size_t count = 0u; known.emplace(banks, count).second; ++count)
    {
        auto iter = std::max_element(banks.begin(), banks.end());
        const auto to_distribute = *iter;

        *iter = 0;
        for (auto& elem : banks)
        {
            elem += (to_distribute / banks.size());
        }

        for (auto i = 0u; i < (to_distribute % banks.size()); ++i)
        {
            if (++iter == banks.end()) { iter = banks.begin(); }
            *iter += 1;
        }
    }

    std::cout << "Redistributions = " << known.size() << std::endl;
    std::cout << "Cycles = " << (known.size() - known[banks]) << std::endl;
    return 0;
}

