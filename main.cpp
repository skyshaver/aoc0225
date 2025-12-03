#include <iostream>
#include <fstream>

int main()
{
    std::ifstream fin("day-one.txt", std::ios::in);
    std::string line;
    while (fin >> line)
    {
        std::cout << line << '\n';
    }
}