#include "default_includes.hpp"
#include "solution.hpp"

static bool is_caught(
        const std::vector<std::pair<int, int>>& scanners,
        int                                     wait)
{
    for (auto [depth, range] : scanners)
    {
        if ((wait + depth) % ((range * 2) - 2) == 0) { return true; }
    }

    return false;
}

template<>
void solve<Day13>(std::istream& ins, std::ostream& outs)
{
    std::vector<std::pair<int, int>> scanners;
    for (std::string line; std::getline(ins, line);)
    {
        std::istringstream iss{line};
        std::string        depth, range;

        iss >> depth;
        iss >> range;
        scanners.emplace_back(std::stoi(depth), std::stoi(range));
    }

    // Part 1
    int severity{0};
    for (auto [depth, range] : scanners)
    {
        if (depth % ((range * 2) - 2) == 0) { severity += (depth * range); }
    }

    outs << "Severity of getting caught: " << severity << std::endl;

    // Part 2
    int wait{0};
    while (is_caught(scanners, wait)) { ++wait; }
    outs << "Delay for not being caught: " << wait << std::endl;
}

