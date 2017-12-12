#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day12>(std::istream& ins, std::ostream& outs)
{
    std::unordered_map<int, int>                     group_map;
    std::unordered_map<int, std::unordered_set<int>> groups;

    int group_id_counter{0};
    for (std::string line; std::getline(ins, line);)
    {
        std::istringstream iss{line};
        std::string        word;
        std::vector<int>   group;

        iss >> word;
        group.emplace_back(std::stoi(word));
        iss >> word; // skip the <->
        while (iss >> word) { group.emplace_back(std::stoi(word)); }

        std::unordered_set<int> to_merge;
        for (int elem : group)
        {
            auto it = group_map.find(elem);
            if (it != group_map.end()) { to_merge.insert(it->second); }
        }

        int group_id = (to_merge.size() > 0)
            ? *(to_merge.begin())
            : group_id_counter++;
        if (to_merge.size() > 1)
        {
            std::for_each(
                    std::next(to_merge.begin()),
                    to_merge.end(),
                    [&](int gid)
                    {
                        groups[group_id].insert(
                                groups[gid].begin(),
                                groups[gid].end());
                        groups.erase(gid);
                    });
        }

        groups[group_id].insert(group.begin(), group.end());
        for (int elem : groups[group_id]) { group_map[elem] = group_id; }
    }

    outs << "Group size of '0' = " << groups[group_map[0]].size() << std::endl
         << "Number of groups  = " << groups.size() << std::endl;
}

