#include "default_includes.hpp"
#include "solution.hpp"

struct component
{
    int  port1 {0};
    int  port2 {0};
    bool used  {false};

    int strength(void) const { return (port1 + port2); }
};

template<>
void solve<Day24>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    std::vector<component> components;
    component comp;
    while ((ins >> comp.port1).ignore(1) >> comp.port2)
    {
        components.emplace_back(std::move(comp));
    }

    auto max_strength     = 0;
    auto longest          = 0;
    auto longest_strength = 0;

    std::function<void(int, int, int)> build_bridges =
        [&] (int port, int strength, int length)
        {
            max_strength = std::max(strength, max_strength);
            longest      = std::max(length, longest);
            if (length == longest)
            {
                longest_strength = std::max(strength, longest_strength);
            }

            for (auto& c : components)
            {
                if (!c.used && ((port == c.port1) || (port == c.port2)))
                {
                    c.used = true;
                    build_bridges(
                            (port == c.port1) ? c.port2 : c.port1,
                            strength + c.strength(),
                            length + 1);
                    c.used = false;
                }
            }
        };

    build_bridges(0, 0, 0);
    outs << "Strength of the strongest bridge = "
         << max_strength << std::endl
         << "Strength of the longest bridge   = "
         << longest_strength << std::endl;
}

