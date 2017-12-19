#include <cassert>

#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day08>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    std::unordered_map<std::string, int> regs;
    std::string                          reg1, reg2, op, comp;
    int                                  val1, val2, total_max {INT_MIN};

    while (ins >> reg1 >> op >> val1 >> reg2 >> reg2 >> comp >> val2)
    {
        if (((comp == ">=") && (regs[reg2] >= val2)) ||
            ((comp == ">")  && (regs[reg2] >  val2)) ||
            ((comp == "==") && (regs[reg2] == val2)) ||
            ((comp == "!=") && (regs[reg2] != val2)) ||
            ((comp == "<=") && (regs[reg2] <= val2)) ||
            ((comp == "<")  && (regs[reg2] <  val2)))
        {
            if      (op == "inc") { regs[reg1] += val1; }
            else if (op == "dec") { regs[reg1] -= val1; }
            else                  { assert(false); }

            if (regs[reg1] > total_max) { total_max = regs[reg1]; }
        }
    }

    auto max {std::max_element(regs.begin(), regs.end(),
            [] (const auto& a1, const auto& a2) {
                return a1.second < a2.second;
            })};
    outs << "Maximum register value = " << max->second << std::endl
         << "Highest overall value  = " << total_max << std::endl;
}

