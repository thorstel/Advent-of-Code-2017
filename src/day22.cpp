#include <cassert>

#include "default_includes.hpp"
#include "solution.hpp"

enum class direction { up, down, left, right };

enum inf_status { clean = 0, weak, infect, flagged };

static constexpr int64_t pos_key(int32_t x, int32_t y)
{
    return ((static_cast<int64_t>(x) & 0xFFFFFFFF) << 32) |
            (static_cast<int64_t>(y) & 0xFFFFFFFF);
}

static constexpr direction next_dir(direction dir, inf_status flag)
{
    switch (flag)
    {
    case inf_status::weak:
        return dir;

    case inf_status::flagged:
        switch (dir)
        {
        case direction::up:    { return direction::down;  }
        case direction::down:  { return direction::up;    }
        case direction::left:  { return direction::right; }
        case direction::right: { return direction::left;  }
        default:               { return direction::up;    }
        }

    default: // clean & infect
        switch (dir)
        {
        case direction::up:
            return (flag == inf_status::infect)
                ? direction::right
                : direction::left;
        case direction::down:
            return (flag == inf_status::infect)
                ? direction::left
                : direction::right;
        case direction::left:
            return (flag == inf_status::infect)
                ? direction::up
                : direction::down;
        case direction::right:
            return (flag == inf_status::infect)
                ? direction::down
                : direction::up;
        default:
            return direction::up; // unreachable
        }
    }
}

static constexpr void move_dir(direction dir, int32_t& x, int32_t& y)
{
    switch (dir)
    {
    case direction::up:    { --y; break; }
    case direction::down:  { ++y; break; }
    case direction::left:  { --x; break; }
    case direction::right: { ++x; break; }
    }
}

static void populate_grid(
        const std::vector<std::string>&          input,
        std::unordered_map<int64_t, inf_status>& grid)
{
    int32_t y {-static_cast<int32_t>(input.size() / 2)};
    for (const auto& row : input)
    {
        int32_t x {-static_cast<int32_t>(row.size() / 2)};
        for (auto c : row)
        {
            grid.emplace(
                    pos_key(x, y),
                    ((c == '#') ? inf_status::infect : inf_status::clean));
            ++x;
        }
        ++y;
    }
}

template<bool Part2 = false>
static size_t calc_infections(
        std::unordered_map<int64_t, inf_status>& grid,
        size_t                                   iterations)
{
    direction dir        {direction::up};
    size_t    num_caused {0u};
    int32_t   x          {0},
              y          {0};
    for (auto _ = 0u; _ < iterations; ++_)
    {
        const auto key = pos_key(x, y);
        const auto inf = grid[key];
        dir = next_dir(dir, inf);

        if (Part2)
        {
            switch (inf)
            {
            case inf_status::clean:
                grid[key] = inf_status::weak;
                break;
            case inf_status::weak:
                grid[key] = inf_status::infect;
                ++num_caused;
                break;
            case inf_status::infect:
                grid[key] = inf_status::flagged;
                break;
            case inf_status::flagged:
                grid[key] = inf_status::clean;
                break;
            default:
                assert(false);
            }
        }
        else
        {
            if (inf == inf_status::clean)
            {
                ++num_caused;
                grid[key] = inf_status::infect;
            }
            else { grid[key] = inf_status::clean; }
        }

        move_dir(dir, x, y);
    }

    return num_caused;
}

template<>
void solve<Day22>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    std::vector<std::string> input {std::istream_iterator<std::string>{ins}, {}};
    assert(input.size() == input.front().size());

    std::unordered_map<int64_t, inf_status> grid;
    populate_grid(input, grid);
    outs << "(Part 1) Number of infections = "
         << calc_infections(grid, 10'000) << std::endl;

    grid.clear();
    populate_grid(input, grid);
    outs << "(Part 2) Number of infections = "
         << calc_infections<true>(grid, 10'000'000) << std::endl;
}

