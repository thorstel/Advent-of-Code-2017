#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day02>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    auto minmax_checksum {0},
         div_checksum    {0};

    for (std::string line; std::getline(ins, line);)
    {
        std::vector<int>   input;
        std::istringstream iss {line};

        for (int i; iss >> i;) { input.push_back(i); }

        auto [min, max] {std::minmax_element(input.begin(), input.end())};
        minmax_checksum += ((*max) - (*min));
        div_checksum    += [&] {
            for (auto i {input.begin()}; i < input.end(); ++i)
            {
                for (auto j {i + 1}; j < input.end(); ++j)
                {
                    if      (((*i) % (*j)) == 0) { return ((*i) / (*j)); }
                    else if (((*j) % (*i)) == 0) { return ((*j) / (*i)); }
                }
            }
            return 0;
        }();
    }

    outs << "(Part 1) Checksum = " << minmax_checksum << std::endl
         << "(Part 2) Checksum = " << div_checksum << std::endl;
}

