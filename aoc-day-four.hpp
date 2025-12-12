#include "utils.hpp"

auto aoc_day_four_main() -> void
{
    auto path = "./test-inputs/day-four.txt";
    auto rows = utils::file_to_vector_of_lines(path);

    // pad rows with empty top/bottom/front/back
    auto row_length = rows[0].size();
    // top
    rows.insert(rows.begin(), std::string(row_length, '.'));
    // bottom
    rows.insert(rows.end(), std::string(row_length, '.'));
    // pad each row with a leading and trailing .
    for (auto &row : rows)
    {
        row.insert(row.begin(), '.');
        row.insert(row.end(), '.');
    }

    auto start_x = 1;
    auto start_y = 1;

    auto end_x = rows[0].size() - 1;
    auto end_y = rows.size() - 1;

    int sum = 0;
    for (size_t y = start_y; y < end_y; y++)
    {
        for (size_t x = start_x; x < end_x; x++)
        {
            if ((rows[y][x]) == '@')
            {
                int acc = 0;
                for (int i : {-1, 0, 1})
                {
                    for (int j : {-1, 0, 1})
                    {
                        if (i == 0 && j == 0)
                        {
                            continue;
                        }
                        else if (rows[y + i][x + j] == '@')
                        {
                            acc++;
                        }
                    }
                }
                if (acc < 4)
                    sum++;
            }
        }
    }
    std::cout << "sum:" << sum << '\n';
}