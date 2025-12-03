#include <iostream>
#include <fstream>
#include <string>
#include <charconv>
#include <optional>

/*
The safe has a dial with only an arrow on it; around the dial are the numbers 0 through 99 in order.
As you turn the dial, it makes a small click noise as it reaches each number.
The attached document (your puzzle input) contains a sequence of rotations, one per line, which tell you how to open the safe.
A rotation starts with an L or R which indicates whether the rotation should be to the left (toward lower numbers) or to the right (toward higher numbers).
Then, the rotation has a distance value which indicates how many clicks the dial should be rotated in that direction.
So, if the dial were pointing at 11, a rotation of R8 would cause the dial to point at 19. After that, a rotation of L19 would cause it to point at 0.
Because the dial is a circle, turning the dial left from 0 one click makes it point at 99. Similarly,
turning the dial right from 99 one click makes it point at 0.
So, if the dial were pointing at 5, a rotation of L10 would cause it to point at 95. After that, a rotation of R5 could cause it to point at 0.
The dial starts by pointing at 50.
You could follow the instructions,
but your recent required official North Pole secret entrance security training seminar taught you that the safe is actually a decoy.
The actual password is the number of times the dial is left pointing at 0 after any rotation in the sequence.
**/

auto to_int = [](std::string_view s) -> std::optional<int>
{
    int value{};
    if (std::from_chars(s.data(), s.data() + s.size(), value).ec == std::errc{})
        return value;
    else
        return std::nullopt;
};

void aoc_day_one_main()
{
    std::ifstream fin("day-one-test.txt", std::ios::in);
    std::string line;
    // dial starts at 50
    int dial = 50;
    // right adds up 99, then starts at 0
    // left subtracts to 0 then subtracts from 99
    unsigned int count = 0;
    // split line to a direction char and number, use simple count logic
    while (fin >> line)
    {
        char direction = line[0];
        int ticks = 0;
        // this isn't safe and makes assumptions about the length etc. of the strings but we'll leave it as toy code
        if (line.size() == 2)
        {
            auto [ptr, ec] = std::from_chars(line.data() + 1, line.data() + 2, ticks);
        }
        else
        {
            auto [ptr, ec] = std::from_chars(line.data() + 1, line.data() + 3, ticks);
        }
        std::cout << "direction: " << direction << " ticks: " << ticks << " line: " << line << '\n';

        if (direction == 'L')
        {
            int start = dial;
            dial = dial - ticks;
            if (dial < 0)
                dial = 100 - (ticks - start);
        }
        else if (direction == 'R')
        {
            int start = dial;
            dial = dial + ticks;
            if (dial > 99)
                dial = (start + ticks) - 100;
        }
        if (dial == 0)
            count++;
        std::cout << "dial pos: " << dial << " count: " << count << '\n';
    }
}