#include "utils.hpp"

auto count_rolls(const std::vector<std::string>& rows) -> int {
    // [row][col]
    auto start_row = 1;
    auto start_col = 1;

    auto end_row = rows.size() - 1;
    auto end_col = rows[0].size() - 1;
    int sum = 0;
    for (size_t r = start_row; r < end_row; r++)
    {
        for (size_t c = start_col; c < end_col; c++)
        {
            if ((rows[r][c]) == '@')
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
                        else if (rows[r + i][c + j] == '@')
                        {
                            acc++;
                        }
                    }
                }
                if (acc < 4) 
                {
                    sum++;
                }
            }
        }
    }    
    return sum;
}


auto count_rolls_and_set_empty_rolls(std::vector<std::string>& rows) -> int {
    // [row][col]
    auto start_row = 1;
    auto start_col = 1;

    auto end_row = rows.size() - 1;
    auto end_col = rows[0].size() - 1;
    std::vector<std::pair<int, int>> remove_list;
    int sum = 0;
    for (size_t r = start_row; r < end_row; r++)
    {
        for (size_t c = start_col; c < end_col; c++)
        {
            if ((rows[r][c]) == '@')
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
                        else if (rows[r + i][c + j] == '@')
                        {
                            acc++;
                        }
                    }
                }
                if (acc < 4)
                {
                    sum++;
                    remove_list.push_back({ r, c });
                }
            }
        }
    }

    for (const auto& e : remove_list)
    {
        rows[e.first][e.second] = '.';
    }

    return sum;
}

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

    // 1505 is the correct answer for part 1
    auto sum = count_rolls(rows);
    std::cout << "sum:" << sum << '\n';

    
    auto total = 0;
    auto s = 0;
    while ((s = count_rolls_and_set_empty_rolls(rows)) != 0)
    {
        total += s;
    }

    std::cout << "total for part 2: " << total << '\n';
    


}