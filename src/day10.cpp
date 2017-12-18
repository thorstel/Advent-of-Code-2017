#include "aoc_utility.hpp"
#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day10>(std::istream& ins, std::ostream& outs)
{
    std::array<unsigned int, 256> list;
    std::iota(list.begin(), list.end(), 0u);

    std::string input;
    ins >> input;

    // Part 1
    std::istringstream        iss {input};
    std::vector<unsigned int> inputs;
    for (std::string s; std::getline(iss, s, ',');)
    {
        inputs.push_back(std::stoi(s));
    }

    auto pos {0u}, skip_size {0u};
    aoc::knot_hash_round(list, inputs, pos, skip_size);
    outs << "(Part 1) Result = " << (list[0] * list[1]) << std::endl;

    // Part 2
    // setup hex output formatting
    auto format {outs.flags()};
    outs << std::setfill('0') << std::hex;

    outs << "(Part 2) Hash   = ";
    for (auto b : aoc::knot_hash(input)) { outs << std::setw(2) << b; }
    outs << std::endl;

    // reset output formatting
    outs.flags(format);
}

