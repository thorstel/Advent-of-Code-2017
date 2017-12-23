#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "solution.hpp"

using timer = std::chrono::high_resolution_clock;

/**********************************************************************
 *                          Local Prototypes                          *
 **********************************************************************/

static void run_day(Day d, std::ostream& outs);
static void select_day(Day d, std::istream& ins, std::ostream& outs);

/**********************************************************************
 *                          Global Functions                          *
 **********************************************************************/

int main(int argc, const char* argv[])
{
    if (argc > 1)
    {
        for (auto i {1}; i < argc; ++i)
        {
            auto day {std::atoi(argv[i]) - 1};
            if ((day >= Day01) && (day < DAY_COUNT))
            {
                run_day(static_cast<Day>(day), std::cout);
            }
            else
            {
                std::cout << "Invalid argument: " << argv[i] << std::endl;
            }
        }
    }
    else
    {
        // execute everything
        for (int i {Day01}; i < DAY_COUNT; ++i)
        {
            run_day(static_cast<Day>(i), std::cout);
        }
    }

#ifdef _MSC_VER
    std::cout << "Press any key to continue . . ." << std::endl;
    std::cin.get();
#endif
    return EXIT_SUCCESS;
}

/**********************************************************************
 *                          Local Functions                           *
 **********************************************************************/

static void run_day(Day d, std::ostream& outs)
{
    outs << "-------------------------------- " << day_to_string(d)
         << " ---------------------------------" << std::endl << std::endl;

    std::ifstream ins {"inputs/" + day_to_string(d) + ".txt"};

    auto start {timer::now()};
    select_day(d, ins, outs);
    auto end   {timer::now()};
    std::chrono::duration<double, std::milli> dur {end - start};

    outs << std::endl << "Execution time: ";
    outs.precision(5);
    outs.setf(std::ios::fixed, std::ios::floatfield);
    outs << dur.count() << " ms" << std::endl << std::endl;
}

static void select_day(Day d, std::istream& ins, std::ostream& outs)
{
    switch (d)
    {
    case Day01:
        solve<Day01>(ins, outs);
        break;
    case Day02:
        solve<Day02>(ins, outs);
        break;
    case Day03:
        solve<Day03>(ins, outs);
        break;
    case Day04:
        solve<Day04>(ins, outs);
        break;
    case Day05:
        solve<Day05>(ins, outs);
        break;
    case Day06:
        solve<Day06>(ins, outs);
        break;
    case Day07:
        solve<Day07>(ins, outs);
        break;
    case Day08:
        solve<Day08>(ins, outs);
        break;
    case Day09:
        solve<Day09>(ins, outs);
        break;
    case Day10:
        solve<Day10>(ins, outs);
        break;
    case Day11:
        solve<Day11>(ins, outs);
        break;
    case Day12:
        solve<Day12>(ins, outs);
        break;
    case Day13:
        solve<Day13>(ins, outs);
        break;
    case Day14:
        solve<Day14>(ins, outs);
        break;
    case Day15:
        solve<Day15>(ins, outs);
        break;
    case Day16:
        solve<Day16>(ins, outs);
        break;
    case Day17:
        solve<Day17>(ins, outs);
        break;
    case Day18:
        solve<Day18>(ins, outs);
        break;
    case Day19:
        solve<Day19>(ins, outs);
        break;
    case Day20:
        solve<Day20>(ins, outs);
        break;
    case Day21:
        solve<Day21>(ins, outs);
        break;
    case Day22:
        solve<Day22>(ins, outs);
        break;
    case Day23:
        solve<Day23>(ins, outs);
        break;
    case Day24:
        solve<Day24>(ins, outs);
        break;
    case Day25:
        solve<Day25>(ins, outs);
        break;
    default:
        outs << "Invalid Day!" << std::endl;
        break;
    }
}

