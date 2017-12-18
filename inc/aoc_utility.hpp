#ifndef AOC_UTILITY_H_
#define AOC_UTILITY_H_

#include <array>
#include <string>
#include <unordered_map>
#include <vector>

namespace aoc {

/**********************************************************************
 *                             Knot Hash                              *
 **********************************************************************/

/**
 * Calculates the "knot hash" for the given input string.
 * @param[in] input String for which the hash is to be calculated.
 * @return Hash for the specified string.
 */
std::array<unsigned int, 16> knot_hash(const std::string& input);

/**
 * Performs a single round of the "knot hash".
 * @param[in,out] array Internal 'working' array of the algorithm.
 * @param[in] inputs Input values to be used for this round.
 * @param[in,out] pos Starting position in the array for this round.
 * After the round is finished, it will contain the starting position
 * for the next round.
 * @param[in,out] skip Skip value which is added after processing each
 * input value to determine the next position. After the round is
 * finished it will contain the starting skip value for the next round.
 */
void knot_hash_round(
        std::array<unsigned int, 256>&   array,
        const std::vector<unsigned int>& inputs,
        unsigned int&                    pos,
        unsigned int&                    skip);

/**********************************************************************
 *                         Number Generation                          *
 **********************************************************************/

/**
 * Generate the next number on the basis of the previous one.
 * @tparam Factor Multiplication factor defining this generator.
 * @param[in] prev Previous value (or starting value) of the generator.
 * @return Next value of the generator.
 */
template<uint64_t Factor>
constexpr uint64_t generator_next(uint64_t prev)
{
    return ((prev * Factor) % 0x7FFFFFFFu);
}

/**
 * Generate the next number which is evenly divisible by the specified
 * criteria value.
 * @tparam Factor Multiplication factor defining this generator.
 * @tparam Criteria Each generated number has to be evenly divisible by
 * this value.
 * @param[in] prev Previous value (or starting value) of the generator.
 * @return Next value of the generator.
 */
template<uint64_t Factor, uint64_t Criteria>
constexpr uint64_t generator_next(uint64_t prev)
{
    auto val {generator_next<Factor>(prev)};
    while ((val % Criteria) != 0u) { val = generator_next<Factor>(val); }
    return val;
}

/**********************************************************************
 *                     Disjoint Sets / Union-Find                     *
 **********************************************************************/

/**
 * Disjoint sets implementation. Adds elements into multiple (disjoint)
 * sets and provides methods to make join existing sets.
 * @tparam T Type of the elements contained in the (disjoint) sets.
 */
template<typename T>
class disjoint_sets
{
    /** Internal data structure of a set. */
    struct set_elem
    {
        T      id;        /**< Parent element / representative of the set. */
        int    rank {0};  /**< Rank of the set (root only). */
        size_t size {0u}; /**< Number of elements in the set (root only). */
    };

    /** Table containing every element across all (disjoint) sets. */
    std::unordered_map<T, set_elem> table;

    /** Total number of disjoint sets tracked by an instance of the class. */
    size_t num_sets {0u};

public:
    /**
     * Finds the set which contains the specified element. If the
     * element is not yet part of any set, a new set will be created.
     * @param[in] elem Element which is to be located.
     * @return Element which acts as representative for the set that
     * contains the specified element.
     */
    T find(const T& elem) { return find_rec(elem).id; }

    /**
     * Implements the "Union" operation of Union-Find. Joins the set
     * containing the first specified element with the set which
     * contains the second specified element.
     * @param[in] elem1 First element whose set is to be joined.
     * @param[in] elem2 Second element whose set is to be joined.
     */
    void make_union(const T& elem1, const T& elem2)
    {
        auto& set1 {find_rec(elem1)};
        auto& set2 {find_rec(elem2)};

        if (set1.id == set2.id) { return; }

        --num_sets;
        if (set1.rank < set2.rank)
        {
            set1.id    = set2.id;
            set2.size += set1.size;
        }
        else
        {
            set2.id    = set1.id;
            set1.size += set2.size;
            if (set1.rank == set2.rank) { ++set1.rank; }
        }
    }

    /**
     * Determines whether the specified element is contained in any of
     * the tracked sets.
     * @param[in] elem Element which is to be looked up.
     * @return True if the element is part of any set.
     */
    bool contains(const T& elem) const
    {
        return table.find(elem) != table.end();
    }

    /**
     * Looks up the size of the set which contains the specified element.
     * @param elem Element whose set size is to be returned.
     * @return Size of the set which contains the specified element.
     */
    size_t size_of_set(const T& elem) { return find_rec(elem).size; }

    /**
     * Returns the total number of disjoint sets.
     * @return Number of disjoint sets.
     */
    size_t set_count(void) const { return num_sets; }

private:
    /**
     * Implements a combination of the "Find" and "MakeSet" operations
     * of Union-Find (recursive).
     * @param elem Element whose set is to be found (or which will be
     * made into a new set).
     * @return Representative of the set which contains the given
     * element.
     */
    set_elem& find_rec(const T& elem)
    {
        auto& set {table[elem]};
        if (set.size == 0u)
        {
            ++num_sets;
            set.id   = elem;
            set.size = 1u;
            return set;
        }
        else if (set.id == elem) { return set; }
        else
        {
            auto& parent {find_rec(set.id)};
            set.id = parent.id;
            return parent;
        }
    }
};

}  // namespace aoc
#endif  // AOC_UTILITY_H_

