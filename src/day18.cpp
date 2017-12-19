#include <cassert>
#include <cctype>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <thread>
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

static std::mutex                        prog_mutex;
static std::condition_variable           prog_cv;
static std::unordered_map<int64_t, bool> prog_status;

template<bool Is_Part2 = false, int64_t Program = 0>
static int64_t exec_prog(
        const std::vector<instr_def>& commands,
        std::queue<int64_t>&          send_queue,
        std::queue<int64_t>&          recv_queue)
{
    const auto                        other {(Program + 1) % 2};
    int64_t                           snd_count {0}, pos {0};
    std::unordered_map<char, int64_t> registers;
    registers['p'] = Program;

    { // Program is not waiting.
        std::lock_guard<std::mutex> guard {prog_mutex};
        prog_status[Program] = false;
    }

    while ((pos >= 0) && (pos < static_cast<int64_t>(commands.size())))
    {
        auto [cmd, reg1, reg2, val] {commands.at(pos++)};
        switch (cmd)
        {
        case instr::snd:
            if (Is_Part2)
            {
                std::lock_guard<std::mutex> guard {prog_mutex};
                ++snd_count;
                send_queue.push(registers[reg1]);
            }
            else { snd_count = registers[reg1]; }
            prog_cv.notify_one();
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
                bool need_wait {false};
                { // Do we need to wait or can we receive right away?
                    std::lock_guard<std::mutex> guard {prog_mutex};
                    if (recv_queue.empty())
                    {
                        prog_status[Program] = true;
                        need_wait            = true;
                    }
                }

                if (need_wait)
                {
                    std::unique_lock<std::mutex> lock {prog_mutex};
                    prog_cv.wait(lock, [&] { return !recv_queue.empty()
                            || (prog_status[other] && send_queue.empty()); });
                }
                { // Now we can receive or we have a deadlock.
                    std::lock_guard<std::mutex> guard {prog_mutex};
                    if (!recv_queue.empty())
                    {
                        registers[reg1] = recv_queue.front();
                        recv_queue.pop();
                        prog_status[Program] = false;
                    }
                    else
                    {
                        prog_cv.notify_one();
                        return snd_count;
                    }
                }
            }
            else if (registers[reg1] != 0) { return snd_count; }
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
    {
        std::lock_guard<std::mutex> guard {prog_mutex};
        prog_status[Program] = true;
    }
    prog_cv.notify_one();
    return snd_count;
}

template<>
void solve<Day18>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

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
    std::queue<int64_t> out0, out1;

    auto part1_result {exec_prog(commands, out0, out1)};
    outs << "Recovered         = " << part1_result << std::endl;

    // Part 1 should not have used the queues.
    assert(out0.empty() && out1.empty());

    // Part 2
    int64_t send_count {0};

    std::thread t0 {[&] { exec_prog<true, 0>(commands, out0, out1); }};
    std::thread t1 {[&] {
        send_count = exec_prog<true, 1>(commands, out1, out0);
    }};

    t0.join();
    t1.join();
    outs << "Sent by Program 1 = " << send_count << std::endl;
}

