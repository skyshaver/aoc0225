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
    std::println("fresh: {}", counter);

    // part 2 needs full list of ids in ranges that are fresh
    // sort the ranges first, use same base < algo as std::pair, then merge rangees
    std::sort(ranges.begin(), ranges.end(), [](auto& a, auto& b) {return a.start < b.start || (a.start == b.start && a.end < b.end);});

    std::vector<utils::product_range> results;
    auto it = ranges.begin();
    auto current = *it;
    it++;
    while (it != ranges.end())
    {
        if (current.end >= it->start)
        {
            current.end = std::max(current.end, it->end);
        }
        else
        {
            results.push_back(current);
            current = *it;
        }
        it++;
    }
    results.push_back(current);

    int64_t total = 0;
    // total is inclusive so add 1 to range
    for (const auto& e : results)
        total += (e.end + 1) - e.start;
    std::println("total range of fresh ids: {}", total);


}