#include <map>

#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day06>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    std::vector<int> banks {std::istream_iterator<int>{ins}, {}};
    std::map<std::vector<int>, size_t> known;

    for (auto count {0u}; known.emplace(banks, count).second; ++count)
    {
        auto       iter          {std::max_element(banks.begin(), banks.end())};
        const auto to_distribute {*iter};

        *iter = 0;
        for (auto& elem : banks)
        {
            elem += (to_distribute / static_cast<int>(banks.size()));
        }

        for (auto _ {0u}; _ < (to_distribute % banks.size()); ++_)
        {
            if (++iter == banks.end()) { iter = banks.begin(); }
            *iter += 1;
        }
    }

    outs << "Redistributions  = " << known.size() << std::endl
         << "Number of cycles = " << (known.size() - known[banks]) << std::endl;
}

