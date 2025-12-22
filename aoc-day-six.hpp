#include "utils.hpp"


/*
123 328  51 64
 45 64  387 23
6 98  215 314
*   +   *   +

*/

auto add_row(std::vector<int64_t> nums, char sign) -> int64_t
{
    if (sign == '+')
    {
        return std::accumulate(nums.begin(), nums.end(), (int64_t)0);
    }
    else if (sign == '*')
    {
        return std::accumulate(nums.begin(), nums.end(), (int64_t)1, std::multiplies<int64_t>());
    }
    return 0;

}

auto aoc_day_six_main() -> void
{
    auto path = "./test_inputs/day-six.txt";
    auto lines = utils::file_to_vector_of_lines(path);
    std::vector<std::vector<std::string>> rows;
    for (const auto& line : lines)
    {
        rows.push_back(utils::split(line, ' '));
    }

    for (auto& row : rows)
    {
        std::erase_if(row, [](auto& s) {return s.empty();});
        // utils::printStringVec((row));
    }

    std::vector<std::vector<int64_t>> nums(rows[0].size());
    for (auto row = rows.begin(); row < rows.end() - 1; row++)
    {
        for (size_t col = 0; col < row->size(); col++)
        {
            nums[col].push_back(*utils::to_int64(row->at(col)));
        }
    }

    size_t count = 0;
    int64_t sum = 0;
    for (const auto& n : nums)
    {
        sum += add_row(n, rows.back().at(count++)[0]);
        std::println("{}", sum);
    }
    std::println("sum: {}", sum);
}