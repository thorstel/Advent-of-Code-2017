#include <cassert>
#include <cctype>

#include "default_includes.hpp"
#include "solution.hpp"

enum class direction { down, left, up, right };

static constexpr void move_dir(direction dir, int& x, int& y)
{
    switch (dir)
    {
        case direction::down:  { ++y; break; }
        case direction::left:  { --x; break; }
        case direction::up:    { --y; break; }
        case direction::right: { ++x; break; }
    }
}

static inline bool can_move(
        const std::vector<std::string>& grid,
        int                             x,
        int                             y,
        direction                       dir)
{
    move_dir(dir, x, y);
    return (x >= 0)
        && (x < static_cast<int>(grid.front().size()))
        && (y >= 0)
        && (y < static_cast<int>(grid.size()))
        && !std::isblank(grid[y][x]);
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
        ++step_ctr;
        move_dir(dir, x, y);

        if (std::isalpha(grid[y][x])) { result << grid[y][x]; }
        else if (grid[y][x] == '+')   { dir = change_dir(grid, x, y, dir); }
    }

    outs << "Letters on the path = " << result.str() << std::endl
         << "Number of steps     = " << step_ctr << std::endl;
}

