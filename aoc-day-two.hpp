#include <iostream>
#include <fstream>
#include <string>
#include <charconv>
#include <optional>
#include <vector>
#include <numeric>
#include <iterator>

/**
    The ranges are separated by commas (,); each range gives its first ID and last ID separated by a dash (-).

    Since the young Elf was just doing silly patterns,
    you can find the invalid IDs by looking for any ID which is made only of some sequence of digits repeated twice.
    So, 55 (5 twice), 6464 (64 twice), and 123123 (123 twice) would all be invalid IDs.

    None of the numbers have leading zeroes; 0101 isn't an ID at all. (101 is a valid ID that you would ignore.)

    Your job is to find all of the invalid IDs that appear in the given ranges. In the above example:

    11-22 has two invalid IDs, 11 and 22.
    95-115 has one invalid ID, 99.
    998-1012 has one invalid ID, 1010.
    1188511880-1188511890 has one invalid ID, 1188511885.
    222220-222224 has one invalid ID, 222222.
    1698522-1698528 contains no invalid IDs.
    446443-446449 has one invalid ID, 446446.
    38593856-38593862 has one invalid ID, 38593859.
    The rest of the ranges contain no invalid IDs.
    Adding up all the invalid IDs in this example produces 1227775554.

 */

void printStringVec(std::vector<std::string> &vec)
{
    for (const auto &e : vec)
        std::cout << e << ' ';
    std::cout << '\n';
}

auto to_int64(std::string_view s) -> std::optional<int64_t>
{
    int64_t value{};
    if (std::from_chars(s.data(), s.data() + s.size(), value).ec == std::errc{})
        return value;
    else
        return std::nullopt;
};

std::vector<std::string> split(const std::string &str, char delim = ' ')
{
    std::vector<std::string> result;
    size_t idx = str.find(delim);
    size_t start = 0;
    while (idx != std::string::npos)
    {
        result.push_back(str.substr(start, idx - start));
        start = idx + 1;
        idx = str.find(delim, idx + 1);
    }
    result.push_back(str.substr(start));
    return result;
}

struct product_range
{
    int64_t start;
    int64_t end;
};

auto split_to_product_range(const std::string &range_str) -> product_range
{
    auto index_of_hyphen = range_str.find('-');
    product_range range{};
    auto start = range_str.substr(0, index_of_hyphen);
    auto end = range_str.substr(index_of_hyphen + 1, range_str.size());
    if (auto s = to_int64(start))
        range.start = *s;
    if (auto e = to_int64(end))
        range.end = *e;
    return range;
}

auto aoc_day_two_main() -> void
{
    std::ifstream fin("./test-inputs/day-two.txt", std::ios::in);
    std::string line;
    // input is one line of comma separated text
    if (fin.is_open())
        fin >> line;

    auto ranges = split(line, ',');
    std::vector<product_range> product_ranges{};
    for (const auto &e : ranges)
    {
        product_ranges.push_back(split_to_product_range(e));
    }

    // size_t i = 0;
    // for (const auto &e : product_ranges)
    // {
    //     std::cout << e.start << ' ' << e.end << ' ' << ranges[i++] << '\n';
    // }
}