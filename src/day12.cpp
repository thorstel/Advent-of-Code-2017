#include "aoc_utility.hpp"
#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day12>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    aoc::disjoint_sets<int> groups;
    for (std::string line; std::getline(ins, line);)
    {
        std::istringstream iss {line};
        std::string        word;
        std::vector<int>   group;

        iss >> word;
        auto set = groups.find(std::stoi(word));
        iss >> word; // skip the <->
        while (iss >> word) { groups.make_union(set, std::stoi(word)); }
    }

    outs << "Group size of '0' = " << groups.size_of_set(0) << std::endl
         << "Number of groups  = " << groups.set_count() << std::endl;
}

