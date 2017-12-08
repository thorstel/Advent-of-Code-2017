#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

static std::map<std::string, std::pair<int, std::vector<std::string>>> towers;

static int get_total_weight(const std::string& name)
{
    std::vector<int> weights;
    std::for_each(
            towers[name].second.begin(),
            towers[name].second.end(),
            [&](const auto& n) { weights.push_back(get_total_weight(n)); });

    if ((weights.size() > 0) &&
        (!std::equal(weights.begin() + 1, weights.end(), weights.begin())))
    {
        std::cout << "Error: " << name << " (" << towers[name].first
                  << ") is imbalanced! Weights: ";
        for (auto i = 0u; i < towers[name].second.size(); ++i)
        {
            std::cout << towers[name].second[i] << " (" << weights[i] << ") ";
        }

        std::cout << std::endl;
    }

    towers[name].second.clear();
    std::for_each(
            weights.begin(),
            weights.end(),
            [&](int& w) { towers[name].first += w; });
    return towers[name].first;
}

int main(void)
{
    // Input handling
    for (std::string line; std::getline(std::cin, line);)
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
            [](auto& t) { (void)get_total_weight(t.first); });
    return 0;
}

