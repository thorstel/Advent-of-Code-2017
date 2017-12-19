#include "default_includes.hpp"
#include "solution.hpp"

template<>
void solve<Day04>(std::istream& ins, std::ostream& outs)
{
    if (!ins.good())
    {
        outs << "Failed to open input file!" << std::endl;
        return;
    }

    unsigned int valid_phrases_p1 {0u},
                 valid_phrases_p2 {0u};
    for (std::string line; std::getline(ins, line);)
    {
        std::unordered_set<std::string> known_p1, known_p2;
        std::istringstream              iss         {line};
        bool                            is_valid_p1 {true},
                                        is_valid_p2 {true};
        for (std::string word; iss >> word;)
        {
            if (!known_p1.insert(word).second) { is_valid_p1 = false; }
            std::sort(word.begin(), word.end());
            if (!known_p2.insert(word).second) { is_valid_p2 = false; }
        }

        if (is_valid_p1) { ++valid_phrases_p1; }
        if (is_valid_p2) { ++valid_phrases_p2; }
    }

    outs << "(Part 1) Valid passphrases = " << valid_phrases_p1 << std::endl
         << "(Part 2) Valid passphrases = " << valid_phrases_p2 << std::endl;
}

