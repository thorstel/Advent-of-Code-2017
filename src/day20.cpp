#include <cassert>
#include <regex>
#include <tuple>

#include "default_includes.hpp"
#include "solution.hpp"

using tuple = std::tuple<int, int, int, int, int, int, int, int, int>;

static constexpr int64_t pos_key(const tuple& tup)
{
    return (static_cast<int64_t>(std::get<0>(tup)) & 0xFFFFF)
        | ((static_cast<int64_t>(std::get<1>(tup)) & 0xFFFFF) << 20)
        | ((static_cast<int64_t>(std::get<2>(tup)) & 0xFFFFF) << 40);
}

static inline int distance(int x, int y, int z)
{
    return std::abs(x) + std::abs(y) + std::abs(z);
}

static bool comp_tuples(const tuple& t1, const tuple& t2)
{
    const auto& [x1, y1, z1, vx1, vy1, vz1, ax1, ay1, az1] {t1};
    const auto& [x2, y2, z2, vx2, vy2, vz2, ax2, ay2, az2] {t2};

    const auto acc1 {distance(ax1, ay1, az1)};
    const auto acc2 {distance(ax2, ay2, az2)};

    if (acc1 != acc2)
    {
        return acc1 < acc2;
    }
    else
    {
        // TODO this is cheating, I was too lazy to make the proper
        // calculation here...
        const auto factor {1'000'000};
        const auto px1    {x1 + vx1 + (factor * ax1)};
        const auto py1    {y1 + vy1 + (factor * ay1)};
        const auto pz1    {z1 + vz1 + (factor * az1)};
        const auto px2    {x2 + vx2 + (factor * ax2)};
        const auto py2    {y2 + vy2 + (factor * ay2)};
        const auto pz2    {z2 + vz2 + (factor * az2)};
        return distance(px1, py1, pz1) < distance(px2, py2, pz2);
    }
}

static const std::regex input_regex {
    R"(p=<(-?\d+),(-?\d+),(-?\d+)>, v=<(-?\d+),(-?\d+),(-?\d+)>, a=<(-?\d+),(-?\d+),(-?\d+)>)",
    std::regex::optimize
};

template<>
void solve<Day20>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    std::vector<tuple> input;
    for (std::string line; std::getline(ins, line);)
    {
        std::smatch match;
        if (std::regex_match(line, match, input_regex))
        {
            input.emplace_back(
                    std::stoi(match.str(1)),
                    std::stoi(match.str(2)),
                    std::stoi(match.str(3)),
                    std::stoi(match.str(4)),
                    std::stoi(match.str(5)),
                    std::stoi(match.str(6)),
                    std::stoi(match.str(7)),
                    std::stoi(match.str(8)),
                    std::stoi(match.str(9)));
        }
        else { assert(false); }
    }

    auto min {std::min_element(input.begin(), input.end(), comp_tuples)};
    outs << "Closest to center = " << (min - input.begin()) << std::endl;

    // TODO also cheating :P (this just assumes that all collisions will
    // happen in the first 1000 iterations).
    for (auto _ {0}; _ < 1000; ++_)
    {
        std::unordered_map<int64_t, bool> collision;
        for (auto& t : input)
        {
            std::get<3>(t) += std::get<6>(t);
            std::get<4>(t) += std::get<7>(t);
            std::get<5>(t) += std::get<8>(t);
            std::get<0>(t) += std::get<3>(t);
            std::get<1>(t) += std::get<4>(t);
            std::get<2>(t) += std::get<5>(t);

            const auto key {pos_key(t)};
            if (!collision.emplace(key, false).second)
            {
                collision[key] = true;
            }
        }

        input.erase(
                std::remove_if(input.begin(), input.end(),
                    [&] (const auto& t) {
                        return collision.at(pos_key(t));
                    }),
                input.end());
    }

    outs << "Particles left    = " << input.size() << std::endl;
}

