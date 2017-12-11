#include <map>

#include "default_includes.hpp"
#include "solution.hpp"

using coords = std::pair<int, int>;

enum Dir {
    Dir_Right,
    Dir_Up,
    Dir_Left,
    Dir_Down,
    Dir_Max
};

static inline Dir next_dir(Dir dir)
{
    return static_cast<Dir>((dir + 1) % Dir_Max);
}

static inline int neighbor_sum(std::map<coords, int>& nodes, int x, int y)
{
    coords neighbor_pos;
    int    sum{0};
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if ((i != 0) || (j != 0))
            {
                neighbor_pos.first  = (x + i);
                neighbor_pos.second = (y + j);
                sum += nodes[neighbor_pos];
            }
        }
    }

    return sum;
}

template<>
void solve<Day03>(std::istream& ins, std::ostream& outs)
{
    int input;
    ins >> input;

    std::map<coords, int>       nodes;
    std::array<coords, Dir_Max> dir_deltas;

    dir_deltas[Dir_Right] = std::make_pair<int, int>(1, 0);
    dir_deltas[Dir_Up]    = std::make_pair<int, int>(0, -1);
    dir_deltas[Dir_Left]  = std::make_pair<int, int>(-1, 0);
    dir_deltas[Dir_Down]  = std::make_pair<int, int>(0, 1);

    auto pos   = std::make_pair<int, int>(0, 0);
    auto dir   = Dir_Right;
    nodes[pos] = 1;
    while (nodes[pos] < input)
    {
        // Next pos and calc sum of neighbors.
        auto [x_d, y_d]  = dir_deltas[dir];
        pos.first       += x_d;
        pos.second      += y_d;
        auto [x, y]      = pos;
        nodes[pos]       = neighbor_sum(nodes, x, y);

        // Check if direction needs to be changed.
        auto [xn_d, yn_d]  = dir_deltas[next_dir(dir)];
        pos.first         += xn_d;
        pos.second        += yn_d;
        if (nodes[pos] == 0) { dir = next_dir(dir); }

        pos.first  = x;
        pos.second = y;
    }

    outs << "(Part 2) Next spiral value = " << nodes[pos] << std::endl;
}

