#include <tuple>

#include "default_includes.hpp"
#include "solution.hpp"

// Using the "3D" cube representation for the hex grid, the distance
// between two positions is
//
//   d = max(|x2 - x1|, |y2 - y1|, |z2 - z1|).
//
// Since we start at position (0, 0, 0), we only need the end position
// to determine the distance.
static constexpr int distance(const std::tuple<int, int, int>& pos)
{
    const auto [x, y, z] {pos};
    return std::max({std::abs(x), std::abs(y), std::abs(z)});
}

template<>
void solve<Day11>(std::istream& ins, std::ostream& outs)
{
    // this step is to strip some potential whitespaces, not really
    // needed for a 'clean' input.
    std::string input;
    ins >> input;

    const std::unordered_map<std::string, std::tuple<int, int, int>> deltas {{
        {"n",  {-1,  1, 0}}, {"ne", {0,  1, -1}}, {"nw", {-1, 0,  1}},
        {"s",  { 1, -1, 0}}, {"sw", {0, -1,  1}}, {"se", { 1, 0, -1}}
    }};

    const std::tuple<int, int, int> start    {0, 0, 0};
    std::tuple<int, int, int>       pos      {start};
    std::istringstream              iss      {input};
    int                             max_dist {0};

    for (std::string dir; std::getline(iss, dir, ',');)
    {
        auto [x, y, z] {deltas.at(dir)};
        std::get<0>(pos) += x;
        std::get<1>(pos) += y;
        std::get<2>(pos) += z;
        max_dist          = std::max(max_dist, distance(pos));
    }

    outs << "(Part 1) Distance     = " << distance(pos) << std::endl
         << "(Part 2) Max distance = " << max_dist << std::endl;
}

