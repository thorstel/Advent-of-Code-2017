#include <cassert>
#include <cctype>

#include "default_includes.hpp"
#include "solution.hpp"

enum class direction { down, left, up, right };

static const std::unordered_map<direction, std::pair<int, int>> deltas {
    {direction::down, {0,  1}}, {direction::left,  {-1, 0}},
    {direction::up,   {0, -1}}, {direction::right, { 1, 0}}
};

static inline bool can_move(
        const std::vector<std::string>& grid,
        int                             x,
        int                             y,
        direction                       dir)
{
    const auto [xd, yd] {deltas.at(dir)};
    return ((x + xd) >= 0)
        && ((x + xd) < static_cast<int>(grid.front().size()))
        && ((y + yd) >= 0)
        && ((y + yd) < static_cast<int>(grid.size()))
        && !std::isblank(grid[y + yd][x + xd]);
}

static direction change_dir(
        const std::vector<std::string>& grid,
        int                             x,
        int                             y,
        direction                       dir)
{
    if ((dir == direction::up) || (dir == direction::down))
    {
        if (can_move(grid, x, y, direction::left)) { return direction::left; }
        else                                       { return direction::right; }
    }
    else
    {
        if (can_move(grid, x, y, direction::up)) { return direction::up; }
        else                                     { return direction::down; }
    }
}

template<>
void solve<Day19>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    std::vector<std::string> grid;
    for (std::string line; std::getline(ins, line);) { grid.push_back(line); }

    // all lines should have the same length!
    assert(std::all_of(grid.begin(), grid.end(),
            [grid] (const auto& s) {
                return s.size() == grid.front().size();
            }));

    const auto start_pos {grid.front().find("|")};
    assert(start_pos != std::string::npos);

    std::ostringstream result;
    auto               dir      {direction::down};
    auto               x        {static_cast<int>(start_pos)};
    auto               y        {0};
    auto               step_ctr {1};
    while (can_move(grid, x, y, dir))
    {
        const auto [xd, yd] {deltas.at(dir)};
        x += xd;
        y += yd;
        ++step_ctr;

        if (std::isalpha(grid[y][x])) { result << grid[y][x]; }
        else if (grid[y][x] == '+')   { dir = change_dir(grid, x, y, dir); }
    }

    outs << "Letters on the path = " << result.str() << std::endl
         << "Number of steps     = " << step_ctr << std::endl;
}

