#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "solution.hpp"

static inline void hash_round(
        std::array<int,256>&    list,
        const std::vector<int>& inputs,
        int&                    pos,
        int&                    skip_size)
{
    for (int len : inputs)
    {
        int start_pos = pos;
        int end_pos   = ((pos + len) - 1) % list.size();

        for (int i = 0; i < (len / 2); ++i)
        {
            std::swap(list[start_pos], list[end_pos]);
            start_pos = (start_pos + 1) % list.size();
            end_pos   = (end_pos > 0) ? (end_pos - 1) : (list.size() - 1);
        }

        pos = (pos + (len + skip_size++)) % list.size();
    }
}

template<>
void solve<Day10>(std::istream& ins, std::ostream& outs)
{
    std::array<int,256> list;
    auto list_setup = [](auto& list) {
        for (int i = 0; i < static_cast<int>(list.max_size()); ++i) {
            list[i] = i;
        }
    };

    std::string input;
    ins >> input;

    // Part 1
    list_setup(list);
    std::istringstream iss{input};
    std::vector<int>   inputs_p1;
    for (std::string s; std::getline(iss, s, ',');)
    {
        inputs_p1.push_back(std::stoi(s));
    }

    int pos{0}, skip_size{0};
    hash_round(list, inputs_p1, pos, skip_size);
    outs << "(Part 1) Result = " << (list[0] * list[1]) << std::endl;

    // Part 2
    list_setup(list);
    std::vector<int> inputs_p2;
    std::for_each(
            input.begin(),
            input.end(),
            [&](auto c) { inputs_p2.push_back(static_cast<int>(c)); });
    for (int i : {17, 31, 73, 47, 23}) { inputs_p2.push_back(i); }

    pos       = 0;
    skip_size = 0;
    for (auto i = 0; i < 64; ++i)
    {
        hash_round(list, inputs_p2, pos, skip_size);
    }

    pos = 0;
    std::array<int, 16> dense_hash{0};
    for (int& elem : dense_hash)
    {
        for (int i = 0; i < 16; ++i) { elem ^= list[pos++]; }
    }

    // setup hex output formatting
    auto format = outs.flags();
    outs << std::setfill('0') << std::hex;

    outs << "(Part 2) Hash = ";
    for (int i : dense_hash) { outs << std::setw(2) << i; }
    outs << std::endl;

    // reset output formatting
    outs.flags(format);
}

