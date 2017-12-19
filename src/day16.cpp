#include <cassert>
#include <regex>
#include <tuple>

#include "default_includes.hpp"
#include "solution.hpp"

static void perform_dance(
        std::string& dancers,
        const std::vector<std::tuple<char, int, int, char, char>>& steps)
{
    for (const auto [cmd, pos1, pos2, elem1, elem2] : steps)
    {
        switch (cmd)
        {
        case 's':
            std::rotate(
                    dancers.begin(),
                    (dancers.begin() + (16 - pos1)),
                    dancers.end());
            break;
        case 'x':
            std::swap(dancers[pos1], dancers[pos2]);
            break;
        case 'p':
            std::iter_swap(
                    std::find(dancers.begin(), dancers.end(), elem1),
                    std::find(dancers.begin(), dancers.end(), elem2));
            break;
        default:
            assert(false);
        }
    }
}

static const std::regex spin_regex     {R"(s(\d+))", std::regex::optimize};
static const std::regex exchange_regex {R"(x(\d+)/(\d+))",
                                        std::regex::optimize};

template<>
void solve<Day16>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    std::string input;
    ins >> input; // cleanup potential whitespaces

    std::istringstream iss     {input};
    std::string        dancers {"abcdefghijklmnop"};

    std::unordered_map<std::string, int> positions;
    positions.emplace(dancers, 0);

    // Record all the dance steps.
    std::vector<std::tuple<char, int, int, char, char>> dance_steps;
    for (std::string cmd; std::getline(iss, cmd, ',');)
    {
        std::smatch match;
        if (cmd[0] == 'p')
        {
            dance_steps.emplace_back('p', 0, 0, cmd[1], cmd[3]);
        }
        else if (std::regex_match(cmd, match, spin_regex))
        {
            const auto num {std::stoi(match.str(1))};
            dance_steps.emplace_back('s', num, 0, ' ', ' ');
        }
        else if (std::regex_match(cmd, match, exchange_regex))
        {
            const auto pos1 {std::stoi(match.str(1))};
            const auto pos2 {std::stoi(match.str(2))};
            dance_steps.emplace_back('x', pos1, pos2, ' ', ' ');
        }
        else { assert(false); }
    }

    // Perform the first dance.
    perform_dance(dancers, dance_steps);
    positions.emplace(dancers, 1);
    outs << "(Part 1) Dancers = " << dancers << std::endl;

    // Perform dances until reaching a previous position of the dancers.
    auto dance_no {2};
    while (dance_no <= 1'000'000'000)
    {
        perform_dance(dancers, dance_steps);
        if (!positions.emplace(dancers, dance_no).second) { break; }
        ++dance_no;
    }

    // Perform the remaining dances.
    const auto remain {(1'000'000'000 - dance_no) %
                       (dance_no - positions[dancers])};
    for (auto _ {0}; _ < remain; ++_) { perform_dance(dancers, dance_steps); }
    outs << "(Part 2) Dancers = " << dancers << std::endl;
}

