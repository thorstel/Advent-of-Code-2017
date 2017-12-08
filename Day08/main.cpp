#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

int main(void)
{
    int total_max = 0;
    std::unordered_map<std::string, int> regs;

    for (std::string line; std::getline(std::cin, line);)
    {
        std::istringstream iss{ line };
        std::string reg;
        std::string op;
        std::string comp;
        std::string reg2;
        int val;
        int val2;

        iss >> reg;
        iss >> op;
        iss >> val;
        iss >> reg2; // skip the if
        iss >> reg2;
        iss >> comp;
        iss >> val2;

        if (((comp == ">=") && (regs[reg2] >= val2)) ||
            ((comp == ">")  && (regs[reg2] > val2))  ||
            ((comp == "==") && (regs[reg2] == val2)) ||
            ((comp == "!=") && (regs[reg2] != val2)) ||
            ((comp == "<=") && (regs[reg2] <= val2)) ||
            ((comp == "<")  && (regs[reg2] < val2)))
        {
            if      (op == "inc") { regs[reg] += val; }
            else if (op == "dec") { regs[reg] -= val; }
            else                  { assert(false); }

            if (regs[reg] > total_max) { total_max = regs[reg]; }
        }
    }

    auto max = std::max_element(
            regs.begin(),
            regs.end(),
            [](const auto& a1, const auto& a2) {
                return a1.second < a2.second;
            });
    std::cout << "Max: [" << max->first << "] = " << max->second << std::endl;
    std::cout << "Highest overall value = " << total_max << std::endl;
    return 0;
}

