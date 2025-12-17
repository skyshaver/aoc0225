#include "utils.hpp"

auto aoc_day_five_main() -> void
{
    auto path = ".//test-inputs/day-five-test.txt";
    auto lines = utils::file_to_vector_of_lines(path);
    auto empty = std::find_if(lines.begin(), lines.end(), [](const auto &str)
                              { return str.empty(); });
    std::cout << std::distance(lines.begin(), empty) << '\n';
    utils::printStringVec(lines);
}