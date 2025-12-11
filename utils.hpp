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

namespace fs = std::filesystem;

namespace utils
{

    auto printStringVec(std::vector<std::string> &vec) -> void
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

    auto split(const std::string &str, char delim = ' ') -> std::vector<std::string>
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

        while (fin >> line)
        {
            lines.push_back(line);
        }
        return lines;
    }
}
