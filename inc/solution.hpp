#ifndef SOLUTION_HPP_
#define SOLUTION_HPP_

#include <fstream>
#include <iostream>
#include <string>

enum Day {
    Day01, Day02, Day03, Day04, Day05,
    Day06, Day07, Day08, Day09, Day10,
    Day11, Day12, Day13, Day14, Day15,
    Day16, Day17, Day18, Day19, Day20,
    Day21, Day22, Day23, Day24, Day25,
    DAY_COUNT
};

std::string day_to_string(Day d);

template<Day D> void solve(std::istream& ins, std::ostream& outs);

#endif  // SOLUTION_HPP_

