#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "solution.hpp"

static std::unordered_map<
        std::string,
        std::pair<int, std::vector<std::string>>> towers;

static int get_total_weight(const std::string& name, std::ostream& outs)
{
    std::vector<int> weights;
    std::for_each(
            towers[name].second.begin(),
            towers[name].second.end(),
            [&](const auto& n) {
                weights.push_back(get_total_weight(n, outs));
            });

    if ((weights.size() > 0) &&
        (!std::equal(weights.begin() + 1, weights.end(), weights.begin())))
    {
        outs << "Error: " << name << " (" << towers[name].first
             << ") is imbalanced! Weights: ";
        for (auto i = 0u; i < towers[name].second.size(); ++i)
        {
            outs << towers[name].second[i] << " (" << weights[i] << ") ";
        }

        outs << std::endl;
    }

    towers[name].second.clear();
    std::for_each(
            weights.begin(),
            weights.end(),
            [&](int& w) { towers[name].first += w; });
    return towers[name].first;
}

template<>
void solve<Day07>(std::istream& ins, std::ostream& outs)
{
    // Input handling
    for (std::string line; std::getline(ins, line);)
    {
        std::istringstream iss{ line };
        std::string name;
        std::string weight;

        auto cleanup = [](unsigned char c) { return !std::isalnum(c); };
        iss >> name;
        iss >> weight;
        weight.erase(
                std::remove_if(weight.begin(), weight.end(), cleanup),
                weight.end());
        towers[name].first = std::stoi(weight);

        for (std::string word; iss >> word;)
        {
            word.erase(
                    std::remove_if(word.begin(), word.end(), cleanup),
                    word.end());
            if (!word.empty())
            {
                towers[name].second.push_back(word);
            }
        }
    }

    // Calculating weights
    std::for_each(
            towers.begin(),
            towers.end(),
            [&](auto& t) { (void)get_total_weight(t.first, outs); });
}

