#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

int main(void)
{
    std::unordered_map<std::string, int> regs;
    std::string reg1, reg2, op, comp;
    int val1, val2, total_max{INT_MIN};

    while (std::cin >> reg1 >> op >> val1 >> reg2 >> reg2 >> comp >> val2)
    {
        if (((comp == ">=") && (regs[reg2] >= val2)) ||
            ((comp == ">")  && (regs[reg2] > val2))  ||
            ((comp == "==") && (regs[reg2] == val2)) ||
            ((comp == "!=") && (regs[reg2] != val2)) ||
            ((comp == "<=") && (regs[reg2] <= val2)) ||
            ((comp == "<")  && (regs[reg2] < val2)))
        {
            if      (op == "inc") { regs[reg1] += val1; }
            else if (op == "dec") { regs[reg1] -= val1; }
            else                  { assert(false); }

            if (regs[reg1] > total_max) { total_max = regs[reg1]; }
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

