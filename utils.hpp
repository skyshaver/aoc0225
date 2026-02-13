#include <iostream>
#include <fstream>
#include <string>
#include <charconv>
#include <optional>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <filesystem>
#include <print>
#include <ranges>

namespace fs = std::filesystem;

namespace utils
{

    auto printStringVec(std::vector<std::string>& vec) -> void
    {
        for (const auto& e : vec)
            std::cout << e << '\n';
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

    auto split(const std::string& str, char delim = ' ') -> std::vector<std::string>
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

    auto to_int = [](std::string_view s) -> std::optional<int>
        {
            int value{};
            if (std::from_chars(s.data(), s.data() + s.size(), value).ec == std::errc{})
                return value;
            else
                return std::nullopt;
        };

    // ifstream will NOT take a string_view as a arg see https://stackoverflow.com/questions/79445302/can-stdifstream-and-stdofstream-be-used-with-a-stdstring-view-filename-arg
    // using >> skips over blank lines like while(fin >> line), getline gets all lines, even blank
    auto file_to_vector_of_lines(fs::path path) -> std::vector<std::string>
    {
        std::ifstream fin(path, std::ios::in);
        std::string line;
        std::vector<std::string> lines;
        if (!fin.is_open())
        {
            std::cout << "file failed to open\n";
            return lines;
        }

        while (std::getline(fin, line))
        {
            lines.push_back(line);
        }
        return lines;
    }

    struct product_range
    {
        int64_t start;
        int64_t end;
    };

    auto split_to_product_range(std::string_view range_str) -> product_range
    {
        auto index_of_hyphen = range_str.find('-');
        product_range range{};
        auto start = range_str.substr(0, index_of_hyphen);
        auto end = range_str.substr(index_of_hyphen + 1, range_str.size());
        if (auto s = utils::to_int64(start))
            range.start = *s;
        if (auto e = utils::to_int64(end))
            range.end = *e;
        return range;
    }

    template<class T>
    void fill_with_range(std::vector<T>& vin, const std::vector<T>& to_copy) {

        auto start = std::begin(vin);
        for (; start < std::end(vin); std::advance(start, to_copy.size())) {
            if (std::distance(start, std::end(vin)) < to_copy.size()) {
                break;
            }
            std::copy(std::begin(to_copy), std::end(to_copy), start);
        }
        if (start < std::end(vin)) {
            std::copy(std::begin(to_copy), std::begin(to_copy) + std::distance(start, std::end(vin)), start);
        }
    }

    template<class T>
    auto fill_vector_with_sequence(const std::vector<T>& sequence, size_t capacity) -> std::vector<T> {

        std::vector<T> vin(capacity);

        auto start = std::begin(vin);
        for (; start < std::end(vin); std::advance(start, sequence.size())) {
            if (std::distance(start, std::end(vin)) < sequence.size()) {
                break;
            }
            std::copy(std::begin(sequence), std::end(sequence), start);
        }
        if (start < std::end(vin)) {
            std::copy(std::begin(sequence), std::begin(sequence) + std::distance(start, std::end(vin)), start);
        }

        return vin;
    }

}
