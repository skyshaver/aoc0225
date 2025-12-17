#include "utils.hpp"

auto aoc_day_five_main() -> void
{
    auto path = ".//test-inputs/day-five.txt";
    auto lines = utils::file_to_vector_of_lines(path);
    auto empty = std::find_if(lines.begin(), lines.end(), [](const auto& str)
        { return str.empty(); });
    std::vector<utils::product_range> ranges;
    for (const auto& line : std::vector<std::string>{ lines.begin(), empty })
    {
        ranges.push_back(utils::split_to_product_range(line));
    }
    std::vector<std::string> ids{ empty + 1, lines.end() };

    // if an id is not in a range it is not fresh, count how many are fresh
    int counter = 0;
    for (const auto& id : ids)
    {
        bool is_fresh = false;
        auto _id = *utils::to_int64(id);
        for (const auto& range : ranges)
        {
            if (_id >= range.start && _id <= range.end)
            {
                is_fresh = true;
            }
        }
        if (is_fresh)
            counter++;

    }
    std::cout << "fresh: " << counter << '\n';
}