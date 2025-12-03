#include <iostream>
#include <fstream>

void aoc_day_one_main()
{
    std::ifstream fin("day-one.txt", std::ios::in);
    std::string line;
    while (fin >> line)
    {
        std::cout << line << '\n';
    }
}