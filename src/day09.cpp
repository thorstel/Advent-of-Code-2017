#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day09>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    char c;
    auto group_depth   = 0,
         total_score   = 0,
         garbage_count = 0;
    bool is_garbage    {false},
         cancel_next   {false};

    while (ins >> c)
    {
        if      (cancel_next)              { cancel_next  = false;         }
        else if (c == '!')                 { cancel_next  = true;          }
        else if (is_garbage && (c != '>')) { ++garbage_count;              }
        else if (c == '<')                 { is_garbage   = true;          }
        else if (c == '>')                 { is_garbage   = false;         }
        else if (c == '{')                 { ++group_depth;                }
        else if (c == '}')                 { total_score += group_depth--; }
        else                               { /* ignore everything else */  }
    }

    outs << "Total Score   = " << total_score << std::endl
         << "Garbage Count = " << garbage_count << std::endl;
}

