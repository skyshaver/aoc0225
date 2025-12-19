#include "utils.hpp"

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

void aoc_day_one_main()
{
    std::ifstream fin("./test_inputs/day-one.txt", std::ios::in);
    std::string line;
    int dial_start = 50;
    size_t count = 0;
    size_t line_count = 1;

    // try creating a buffer from 0 - 99 and then moving an iterator/pointer?
    std::vector<int> dial_counter(100);
    std::iota(dial_counter.begin(), dial_counter.end(), 0);
    auto dial_position = dial_counter.begin();
    std::advance(dial_position, dial_start);
    while (fin >> line)
    {
        char direction = line[0];
        int ticks = 0;
        // this isn't safe and makes assumptions about the length etc. of the strings but we'll leave it as toy code
        // we know first char is L or R so take the rest of the string as an int
        auto [ptr, ec] = std::from_chars(line.data() + 1, line.data() + line.size(), ticks);

        std::cout << line_count << ": direction: " << direction << " ticks: " << ticks << " line: " << line << '\n';

        if (direction == 'L')
        {
            for (size_t i = ticks; i > 0; i--)
            {
                if (dial_position == dial_counter.begin())
                    dial_position = dial_counter.end();

                dial_position = std::prev(dial_position, 1);
            }
        }
        else if (direction == 'R')
        {
            for (size_t i = 0; i < ticks; i++)
            {

                dial_position = std::next(dial_position, 1);

                if (dial_position == dial_counter.end())
                    dial_position = dial_counter.begin();
            }
        }
        if (*dial_position == 0)
            count++;
        std::cout << line_count++ << ": dial pos: " << *dial_position << " count: " << count << '\n';
    }
}

void aoc_day_one_pt2_main()
{
    std::ifstream fin("./test_inputs/day-one.txt", std::ios::in);
    std::string line;
    int dial_start = 50;
    size_t count = 0;

    std::vector<int> dial_counter(100);
    std::iota(dial_counter.begin(), dial_counter.end(), 0);
    auto dial_position = dial_counter.begin();
    std::advance(dial_position, dial_start);

    // this time count whenever we pass 0 which is dial_counter.begin()
    while (fin >> line)
    {
        char direction = line[0];
        int ticks = 0;
        auto [ptr, ec] = std::from_chars(line.data() + 1, line.data() + line.size(), ticks);

        if (direction == 'L')
        {
            for (size_t i = ticks; i > 0; i--)
            {
                if (dial_position == dial_counter.begin())
                {
                    dial_position = dial_counter.end();
                    count++;
                }

                dial_position = std::prev(dial_position, 1);
            }
        }
        else if (direction == 'R')
        {
            for (size_t i = 0; i < ticks; i++)
            {

                if (dial_position == dial_counter.begin())
                    count++;

                dial_position = std::next(dial_position, 1);

                if (dial_position == dial_counter.end())
                    dial_position = dial_counter.begin();
            }
        }
    }

    std::cout << " count: " << count << '\n';
}