#include <cassert>
#include <cctype>
#include <deque>
#include <tuple>

#include "default_includes.hpp"
#include "solution.hpp"

enum class instr { snd, set, add, mul, mod, rcv, jgz };

using instr_def = std::tuple<instr, char, char, int64_t>;

static instr from_string(const std::string& command)
{
    static const std::unordered_map<std::string, instr> lookup {
        {"snd", instr::snd}, {"set", instr::set}, {"add", instr::add},
        {"mul", instr::mul}, {"mod", instr::mod}, {"rcv", instr::rcv},
        {"jgz", instr::jgz}
    };

    return lookup.at(command);
}

template<bool Is_Part2 = false>
static std::pair<int64_t, bool> exec_prog(
        const std::vector<instr_def>&      commands,
        int64_t&                           pos,
        std::unordered_map<char, int64_t>& registers,
        std::deque<int64_t>&               send_queue,
        std::deque<int64_t>&               recv_queue)
{
    int64_t snd_count {0};

    while ((pos >= 0) && (pos < static_cast<int64_t>(commands.size())))
    {
        auto [cmd, reg1, reg2, val] {commands.at(pos++)};
        switch (cmd)
        {
        case instr::snd:
            if (Is_Part2)
            {
                ++snd_count;
                send_queue.push_back(registers[reg1]);
            }
            else { snd_count = registers[reg1]; }
            break;

        case instr::set:
            registers[reg1] = ((reg2 == 0) ? val : registers[reg2]);
            break;

        case instr::add:
            registers[reg1] += ((reg2 == 0) ? val : registers[reg2]);
            break;

        case instr::mul:
            registers[reg1] *= ((reg2 == 0) ? val : registers[reg2]);
            break;

        case instr::mod:
            registers[reg1] %= ((reg2 == 0) ? val : registers[reg2]);
            break;

        case instr::rcv:
            if (Is_Part2)
            {
                if (!recv_queue.empty())
                {
                    registers[reg1] = recv_queue.front();
                    recv_queue.pop_front();
                }
                else
                {
                    --pos;
                    return {snd_count, false};
                }
            }
            else if (registers[reg1] != 0) { return {snd_count, true}; }
            break;

        case instr::jgz:
            if (!std::isalpha(reg1) || registers[reg1] > 0)
            {
                pos = (pos - 1) + ((reg2 == 0) ? val : registers[reg2]);
            }
            break;

        default:
            assert(false);
        }
    }

    return {snd_count, true};
}

template<>
void solve<Day18>(std::istream& ins, std::ostream& outs)
{
    std::vector<instr_def> commands;

    // Input parsing
    for (std::string line; std::getline(ins, line);)
    {
        std::istringstream iss {line};
        std::string        cmd;

        iss >> cmd;
        instr command {from_string(cmd)};
        if ((command == instr::snd) || (command == instr::rcv))
        {
            char reg;
            iss >> reg;
            commands.emplace_back(command, reg, 0, 0);
        }
        else
        {
            char        reg;
            std::string val;

            iss >> reg;
            iss >> val;
            if (std::isalpha(val[0]))
            {
                commands.emplace_back(command, reg, val[0], 0);
            }
            else
            {
                commands.emplace_back(command, reg, 0, std::stoll(val));
            }
        }
    }

    // Part 1
    int64_t                           pos {0};
    std::deque<int64_t>               out0, out1;
    std::unordered_map<char, int64_t> registers;

    auto part1_result {exec_prog(commands, pos, registers, out0, out1).first};
    outs << "Recovered         = " << part1_result << std::endl;

    // Part 1 should not have used the queues.
    assert(out0.empty() && out1.empty());

    // Part 2
    int64_t                           pos0 {0}, pos1 {0}, send_count {0};
    std::unordered_map<char, int64_t> regs0, regs1 {{'p', 1}};
    while (true)
    {
        auto [count0, done0] {exec_prog<true>(commands, pos0, regs0, out0, out1)};
        auto [count1, done1] {exec_prog<true>(commands, pos1, regs1, out1, out0)};

        NOT_USED(count0);
        send_count += count1;

        // Stop if both programs terminated.
        if (done0 && done1) { break; }

        // Stop if a deadlock occurred.
        if (!done0 && out0.empty() && !done1 && out1.empty()) { break; }
    }

    outs << "Sent by Program 1 = " << send_count << std::endl;
}

