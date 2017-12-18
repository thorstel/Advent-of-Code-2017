#include "default_includes.hpp"
#include "solution.hpp"

enum Dir {
    Dir_Right,
    Dir_Up,
    Dir_Left,
    Dir_Down,
    Dir_Max
};

static constexpr int64_t coords_key(int32_t x, int32_t y)
{
    return (static_cast<int64_t>(*reinterpret_cast<uint32_t*>(&x)) << 32)
        | (*reinterpret_cast<uint32_t*>(&y));
}

static constexpr Dir next_dir(Dir dir)
{
    return static_cast<Dir>((dir + 1) % Dir_Max);
}

static int neighbor_sum(
        std::unordered_map<int64_t, int>& nodes,
        int32_t                           x,
        int32_t                           y)
{
    static const std::array<std::pair<int32_t, int32_t>, 8> deltas{{
        { 0, 1}, {1,  0}, { 1, 1}, { 1, -1},
        {-1, 1}, {0, -1}, {-1, 0}, {-1, -1}
    }};

    return std::accumulate(deltas.begin(), deltas.end(), 0,
            [&] (int sum, const std::pair<int32_t, int32_t>& p) {
                auto [x_d, y_d] {p};
                return sum + nodes[coords_key((x + x_d), (y + y_d))];
            });
}

template<>
void solve<Day03>(std::istream& ins, std::ostream& outs)
{
    NOT_USED(ins);

    int                                              input {289326};
    std::unordered_map<int64_t, int>                 nodes;
    std::array<std::pair<int32_t, int32_t>, Dir_Max> dir_deltas;

    dir_deltas[Dir_Right] = { 1,  0};
    dir_deltas[Dir_Up]    = { 0, -1};
    dir_deltas[Dir_Left]  = {-1,  0};
    dir_deltas[Dir_Down]  = { 0,  1};

    auto    dir {Dir_Right};
    int32_t x   {0},
            y   {0};
    nodes[coords_key(x, y)] = 1;

    while (nodes[coords_key(x, y)] < input)
    {
        // Next pos and calc sum of neighbors.
        auto [x_d, y_d] {dir_deltas[dir]};
        x += x_d;
        y += y_d;
        nodes[coords_key(x, y)] = neighbor_sum(nodes, x, y);

        // Check if direction needs to be changed.
        auto [xn_d, yn_d] {dir_deltas[next_dir(dir)]};
        if (nodes[coords_key((x + xn_d), (y + yn_d))] == 0)
        {
            dir = next_dir(dir);
        }
    }

    outs << "(Part 2) Next spiral value = "
         << nodes[coords_key(x, y)] << std::endl;
}

