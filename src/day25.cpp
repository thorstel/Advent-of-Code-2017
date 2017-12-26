#include <deque>

#include "default_includes.hpp"
#include "solution.hpp"

enum class state { A, B, C, D, E, F };
enum class dir   { left, right };

template<>
void solve<Day25>(std::istream& ins, std::ostream& outs)
{
    NOT_USED(ins);

    const auto          steps      {12'425'180};
    state               curr_state {state::A};
    std::deque<uint8_t> tape       {0};
    auto                cursor     {tape.begin()};

    auto move_cursor = [&tape, &cursor] (dir d) {
        if (d == dir::left)
        {
            if (cursor == tape.begin())
            {
                tape.push_front(0);
                cursor = tape.begin();
            }
            else { --cursor; }
        }
        else
        {
            if (std::next(cursor) == tape.end())
            {
                tape.push_back(0);
                cursor = tape.end() - 1;
            }
            else { ++cursor; }
        }
    };

    for (auto _ {0}; _ < steps; ++_)
    {
        // Implementation & input description side-by-side.
        switch (curr_state)
        {
        case state::A:                   // In state A:
            if (*cursor == 0)            //   If the current value is 0:
            {
                *cursor = 1;             //     - Write the value 1.
                move_cursor(dir::right); //     - Move one slot to the right.
                curr_state = state::B;   //     - Continue with state B.
            }
            else                         //   If the current value is 1:
            {
                *cursor = 0;             //     - Write the value 0.
                move_cursor(dir::right); //     - Move one slot to the right.
                curr_state = state::F;   //     - Continue with state F.
            }
            break;

        case state::B:                   // In state B:
            if (*cursor == 0)            //   If the current value is 0:
            {
                *cursor = 0;             //     - Write the value 0.
                move_cursor(dir::left);  //     - Move one slot to the left.
                curr_state = state::B;   //     - Continue with state B.
            }
            else                         //   If the current value is 1:
            {
                *cursor = 1;             //     - Write the value 1.
                move_cursor(dir::left);  //     - Move one slot to the left.
                curr_state = state::C;   //     - Continue with state C.
            }
            break;

        case state::C:                   // In state C:
            if (*cursor == 0)            //   If the current value is 0:
            {
                *cursor = 1;             //     - Write the value 1.
                move_cursor(dir::left);  //     - Move one slot to the left.
                curr_state = state::D;   //     - Continue with state D.
            }
            else                         //     - Continue with state D.
            {
                *cursor = 0;             //     - Write the value 0.
                move_cursor(dir::right); //     - Move one slot to the right.
                curr_state = state::C;   //     - Continue with state C.
            }
            break;

        case state::D:                   // In state D:
            if (*cursor == 0)            //   If the current value is 0:
            {
                *cursor = 1;             //     - Write the value 1.
                move_cursor(dir::left);  //     - Move one slot to the left.
                curr_state = state::E;   //     - Continue with state E.
            }
            else                         //   If the current value is 1:
            {
                *cursor = 1;             //     - Write the value 1.
                move_cursor(dir::right); //     - Move one slot to the right.
                curr_state = state::A;   //     - Continue with state A.
            }
            break;

        case state::E:                   // In state E:
            if (*cursor == 0)            //   If the current value is 0:
            {
                *cursor = 1;             //     - Write the value 1.
                move_cursor(dir::left);  //     - Move one slot to the left.
                curr_state = state::F;   //     - Continue with state F.
            }
            else                         //   If the current value is 1:
            {
                *cursor = 0;             //     - Write the value 0.
                move_cursor(dir::left);  //     - Move one slot to the left.
                curr_state = state::D;   //     - Continue with state D.
            }
            break;

        case state::F:                   // In state F:
            if (*cursor == 0)            //   If the current value is 0:
            {
                *cursor = 1;             //     - Write the value 1.
                move_cursor(dir::right); //     - Move one slot to the right.
                curr_state = state::A;   //     - Continue with state A.
            }
            else                         //   If the current value is 1:
            {
                *cursor = 0;             //     - Write the value 0.
                move_cursor(dir::left);  //     - Move one slot to the left.
                curr_state = state::E;   //     - Continue with state E.
            }
            break;
        }
    }

    outs << "Diagnostic Checksum = "
         << std::count_if(tape.begin(), tape.end(),
                 [] (auto i) { return i == 1; })
         << std::endl;
}

