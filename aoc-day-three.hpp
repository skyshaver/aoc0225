#include <iostream>
#include <fstream>
#include <string>
#include <charconv>
#include <optional>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>

auto to_int64(std::string_view s) -> std::optional<int64_t>
{
    int64_t value{};
    if (std::from_chars(s.data(), s.data() + s.size(), value).ec == std::errc{})
        return value;
    else
        return std::nullopt;
};

// part one need to find the two digits that make the highest number IN ORDER
/**
    In 987654321111111, you can make the largest joltage possible, 98, by turning on the first two batteries.
    In 811111111111119, you can make the largest joltage possible by turning on the batteries labeled 8 and 9, producing 89 jolts.
    In 234234234234278, you can make 78 by turning on the last two batteries (marked 7 and 8).
    In 818181911112111, the largest joltage you can produce is 92.
 */
auto aoc_day_three_main() -> void
{
    std::ifstream fin("./test-inputs/day-three.txt", std::ios::in);
    std::string line;
    std::vector<std::string> lines;
    if (!fin.is_open())
    {
        std::cout << "file failed to open\n";
    }

    while (fin >> line)
    {
        lines.push_back(line);
    }

    // max not including last digit, and then max in rest of range?
    int sum = 0;
    for (const auto &e : lines)
    {
        auto first = std::max_element(e.begin(), e.end() - 1);
        auto second = std::max_element(first + 1, e.end());
        std::string pair{*first, *second};
        if (auto n = to_int64(pair))
        {
            sum += *n;
        }
    }
    std::cout << sum << '\n';
}