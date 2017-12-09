#include <iostream>

int main(void)
{
    char c;
    int  group_depth   = 0;
    int  total_score   = 0;
    int  garbage_count = 0;
    bool is_garbage    = false;
    bool cancel_next   = false;

    while (std::cin >> c)
    {
        if      (cancel_next)              { cancel_next = false;          }
        else if (c == '!')                 { cancel_next = true;           }
        else if (is_garbage && (c != '>')) { ++garbage_count;              }
        else if (c == '<')                 { is_garbage = true;            }
        else if (c == '>')                 { is_garbage = false;           }
        else if (c == '{')                 { ++group_depth;                }
        else if (c == '}')                 { total_score += group_depth--; }
        else                               { /* ignore everything else */  }
    }

    std::cout << "Total Score = " << total_score << std::endl;
    std::cout << "Garbage Count = " << garbage_count << std::endl;
    return 0;
}

