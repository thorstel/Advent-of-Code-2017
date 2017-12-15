#ifndef AOC_UTILITY_H_
#define AOC_UTILITY_H_

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

namespace aoc
{
/**********************************************************************
 *                             KNOT HASH                              *
 **********************************************************************/

std::array<unsigned int, 16> knot_hash(const std::string& input);

void knot_hash_round(
        std::array<unsigned int, 256>&   array,
        const std::vector<unsigned int>& inputs,
        unsigned int&                    pos,
        unsigned int&                    skip);

/**********************************************************************
 *                     DISJOINT SETS / UNION FIND                     *
 **********************************************************************/

template<typename T>
class disjoint_sets
{
    struct set { T id; size_t size{0u}; };

    std::unordered_map<T, set> table;
    size_t                     num_sets{0u};

public:
    T find(const T& t) { return find_rec(t).id; }

    void make_union(const T& t1, const T& t2)
    {
        auto& s1 = find_rec(t1);
        auto& s2 = find_rec(t2);

        if (s1.id != s2.id)
        {
            --num_sets;
            s2.id    = s1.id;
            s1.size += s2.size;
        }
    }

    bool contains(const T& t) const { return table.find(t) != table.end(); }

    size_t size_of_set(const T& t) { return find_rec(t).size; }

    size_t set_count() const { return num_sets; }

private:
    set& find_rec(const T& t)
    {
        auto& s = table[t];
        if (s.size == 0u)
        {
            ++num_sets;
            s.id   = t;
            s.size = 1u;
            return s;
        }
        else if (s.id == t) { return s; }
        else
        {
            auto& p = find_rec(s.id);
            s.id    = p.id;
            return p;
        }
    }
};

}
#endif  // AOC_UTILITY_H_

