#include <cassert>

#include "default_includes.hpp"
#include "solution.hpp"

static inline std::string mirror(const std::string& grid);
static inline std::string rotate(const std::string& grid);

static size_t count_pixels(
        const std::unordered_map<std::string, std::string>& rules,
        const std::string&                                  start_grid,
        int                                                 iterations)
{
    std::string grid {start_grid};
    for (auto _ {0}; _ < iterations; ++_)
    {
        const auto dim   {grid.find('/')};
        const auto slice {((dim % 2) == 0) ? 2 : 3};

        std::ostringstream oss;
        for (auto i {0u}; i < (dim / slice); ++i)
        {
            std::vector<std::string> sub_grids;
            for (auto j {0u}; j < (dim / slice); ++j)
            {
                const auto row  {i * slice * (dim + 1)};
                const auto row2 {row + (dim + 1)};
                const auto col  {j * slice};
                if (slice == 2)
                {
                    sub_grids.emplace_back(rules.at(std::string{
                            grid[row  + col], grid[row  + col + 1], '/',
                            grid[row2 + col], grid[row2 + col + 1]}));
                }
                else
                {
                    const auto row3 {row2 + (dim + 1)};
                    sub_grids.emplace_back(rules.at(std::string{
                            grid[row  + col], grid[row  + col + 1], grid[row  + col + 2], '/',
                            grid[row2 + col], grid[row2 + col + 1], grid[row2 + col + 2], '/',
                            grid[row3 + col], grid[row3 + col + 1], grid[row3 + col + 2]}));
                }
            }

            for (auto j {0}; j < (slice + 1); ++j)
            {
                for (auto& g : sub_grids)
                {
                    oss << g.substr((j * (slice + 2)), (slice + 1));
                }
                if (j < slice) { oss << '/'; }
            }

            if ((i + 1) < (dim / slice)) { oss << '/'; }
        }

        grid = oss.str();
    }

    return std::count_if(grid.begin(), grid.end(),
            [] (auto c) { return c == '#'; });
}

template<>
void solve<Day21>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    std::unordered_map<std::string, std::string> rules;
    std::string rule, enhance;
    while (ins >> rule >> enhance >> enhance)
    {
        rules.emplace(rule, enhance);
        rules.emplace(mirror(rule), enhance);
        rule = rotate(rule);
        rules.emplace(rule, enhance);
        rules.emplace(mirror(rule), enhance);
        rule = rotate(rule);
        rules.emplace(rule, enhance);
        rules.emplace(mirror(rule), enhance);
        rule = rotate(rule);
        rules.emplace(rule, enhance);
        rules.emplace(mirror(rule), enhance);
    }

    const std::string start {".#./..#/###"};
    outs << "Pixels after 5 iterations  = "
         << count_pixels(rules, start, 5) << std::endl
         << "Pixels after 18 iterations = "
         << count_pixels(rules, start, 18) << std::endl;
}

/**********************************************************************
 *                          Helper Functions                          *
 **********************************************************************/

static inline std::string mirror(const std::string& grid)
{
    if (grid.size() == 5)
    {
        return std::string{grid[1], grid[0], '/',
                           grid[4], grid[3]};
    }
    else if (grid.size() == 11)
    {
        return std::string{grid[2],  grid[1], grid[0], '/',
                           grid[6],  grid[5], grid[4], '/',
                           grid[10], grid[9], grid[8]};
    }
    else { assert(false); return ""; }
}

static inline std::string rotate(const std::string& grid)
{
    if (grid.size() == 5)
    {
        return std::string{grid[3], grid[0], '/',
                           grid[4], grid[1]};
    }
    else if (grid.size() == 11)
    {
        return std::string{grid[8],  grid[4], grid[0], '/',
                           grid[9],  grid[5], grid[1], '/',
                           grid[10], grid[6], grid[2]};
    }
    else { assert(false); return ""; }
}

