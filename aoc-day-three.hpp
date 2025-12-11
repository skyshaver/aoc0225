#include "utils.hpp"

// part one need to find the two digits that make the highest number IN ORDER
/**
    In 987654321111111, you can make the largest joltage possible, 98, by turning on the first two batteries.
    In 811111111111119, you can make the largest joltage possible by turning on the batteries labeled 8 and 9, producing 89 jolts.
    In 234234234234278, you can make 78 by turning on the last two batteries (marked 7 and 8).
    In 818181911112111, the largest joltage you can produce is 92.
 */
auto aoc_day_three_main() -> void
{
    auto path = "./test-inputs/day-three.txt";

    auto lines = utils::file_to_vector_of_lines(path);

    // part 1
    // max not including last digit, and then max in rest of range?
    // for (const auto &e : lines)
    // {
    //     auto first = std::max_element(e.begin(), e.end() - 1);
    //     auto second = std::max_element(first + 1, e.end());
    //     std::string pair{*first, *second};
    //     if (auto n = to_int64(pair))
    //     {
    //         sum += *n;
    //     }
    // }

    // part 2, find the 12 digits that make max number

    // || 987 || 6543 2111 1111 -> 9876 5432 1111
    //  || 9 || 87  || 6543 2111 1111  max + 1 -> end - 12
    // || 234 || 2342 3423 4278 -> 4342 3423 4278
    // || 818 || 1819 1111 2111 -> 8889 1111 2111
    int64_t sum = 0;
    // add max from range excluding final 12 - solution.size?
    for (const auto &e : lines)
    {

        std::string prefix{e.begin(), e.end() - 11};
        std::string suffix(e.end() - 11, e.end());
        auto p_iter = std::max_element(prefix.begin(), prefix.end());
        // erase from start of prefix to max
        prefix.erase(prefix.begin(), p_iter);
        std::string mutated{prefix.substr(1, prefix.size() - 1) + suffix};
        std::string solution{prefix[0]};

        auto s_iter = mutated.begin();
        while (solution.size() < 12)
        {
            s_iter = std::max_element(s_iter, mutated.end() - (11 - solution.size()));
            solution.push_back(*s_iter);
            s_iter++;
        }

        if (auto n = utils::to_int64(solution))
        {
            sum += *n;
            // std::cout << solution << '\n';
        }
    }
    std::cout << "sum: " << sum << '\n';

    // 373 3444 4443 3724 4341 4634 5246 3644 2344 9 335 41445 8 443 3344 4254 4445 3534 4544 4434 3444 3243 3545 4446 4233 4344 4472
}

/**
 *
 *
 *
 *         // std::string prefix{e.begin(), e.end() - 12};
        // std::string suffix(e.end() - 12, e.end());
        // change this to find the first max element
        std::string mutated{e};
        // find max in prefix 987 -> 9: no change
        auto p_iter = std::max_element(mutated.begin(), mutated.end());
        // erase from start of prefix to max
        mutated.erase(mutated.begin(), p_iter);
        // check if any elements in prefix after max are equal to or greater than max and any element in suffix, set to 0 otherwise then remove?
        // maybe just rejoin prefix and suffix here? and then do remove min_elem till 12?
        // std::string mutated{prefix + suffix};
        // // remove 12 - prefix min)_elements from suffix
        while (mutated.size() > 12)
        {
            auto s_iter = std::min_element(mutated.begin(), mutated.end());
            mutated.erase(s_iter);
        }

        if (auto n = to_int64(mutated))
        {
            sum += *n;
            std::cout << mutated << '\n';
        }
 */