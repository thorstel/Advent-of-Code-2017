#include <cassert>
#include <cctype>
#include <tuple>

#include "default_includes.hpp"
#include "solution.hpp"

enum class instr { set, sub, mul, jnz };

using instr_def = std::tuple<instr, char, char, int64_t>;

// Part 1: Count the number of times 'mul' is executed.
static size_t count_mul(const std::vector<instr_def>& commands)
{
    std::unordered_map<char, int64_t> registers;
    int64_t pos {0};
    size_t  cnt {0};
    while ((pos >= 0) && (pos < static_cast<int64_t>(commands.size())))
    {
        const auto& [cmd, reg1, reg2, value] {
            commands.at(static_cast<size_t>(pos))};

        bool jumped {false};
        switch (cmd)
        {
        case instr::set:
            registers[reg1] = (reg2 == 0) ? value : registers.at(reg2);
            break;
        case instr::sub:
            registers[reg1] -= (reg2 == 0) ? value : registers.at(reg2);
            break;
        case instr::mul:
            registers[reg1] *= (reg2 == 0) ? value : registers.at(reg2);
            ++cnt;
            break;
        case instr::jnz:
            if ((std::isdigit(reg1) && (reg1 != '0')) ||
                (registers[reg1] != 0))
            {
                pos    += (reg2 == 0) ? value : registers.at(reg2);
                jumped  = true;
            }
            break;
        default:
            assert(false);
            break;
        }

        if (!jumped) { ++pos; }
    }

    return cnt;
}

// Translation of the assembler from the input file.
static int64_t exec_part2(void)
{
    int64_t h {0};

    for (int64_t b {107'900}; b <= 124'900; b += 17)
    {
        for (int64_t d {2}; d < b; ++d)
        {
            // The following loop from the assembler
            // for (int64_t e {2}; e < b; ++e)
            // {
            //     if ((d * e) == b) { ++h; break; }
            // }
            // is not necessary with the modulus operator:
            if ((b % d) == 0) { ++h; break; }
        }
    }

    return h;
}

template<>
void solve<Day23>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    const std::unordered_map<std::string, instr> instr_map {
        {"set", instr::set}, {"sub", instr::sub},
        {"mul", instr::mul}, {"jnz", instr::jnz}};

    std::vector<instr_def> commands;
    std::string            cmd, val;
    char                   reg;
    while (ins >> cmd >> reg >> val)
    {
        if (std::isalpha(val[0]))
        {
            commands.emplace_back(instr_map.at(cmd), reg, val[0], 0);
        }
        else
        {
            commands.emplace_back(instr_map.at(cmd), reg, 0, std::stoll(val));
        }
    }

    outs << "(Part 1) Number of 'mul' invocations = " << count_mul(commands)
         << std::endl;
    outs << "(Part 2) Value of register 'h'       = " << exec_part2()
         << std::endl;
}

