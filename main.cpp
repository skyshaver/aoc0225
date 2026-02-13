// #include "aoc-day-one.hpp"
// #include "aoc-day-two.hpp"
// #include "aoc-day-three.hpp"
// #include "aoc-day-four.hpp"
// #include "aoc-day-five.hpp"
#include "aoc-day-six.hpp"


int main()
{
    // aoc_day_one_main();
    // aoc_day_one_pt2_main();
    // aoc_day_two_main();
    // aoc_day_three_main();
    // aoc_day_four_main();
    // aoc_day_five_main();
    // aoc_day_six_main();
    std::println("{}", sizeof(float));
    std::vector<float> nyquist(48'000);
    std::println("{}, {}", sizeof(nyquist), nyquist.size());
    // std::ranges::generate(nyquist, [](){ return })
    // std::vector<float> nyq(48'000);
    // std::ranges::copy_n(std::views::repeat({-1.0, 1.0}), nyquist.size(), std::begin(nyquist));
    std::vector<float> vin(27);
    std::vector<float> to_copy(11);
    std::iota(std::begin(to_copy), std::end(to_copy), 1.f);
    utils::fill_with_range(vin, to_copy);
    for (const auto& e : vin)
        std::cout << e << ' ';
    std::cout << '\n';

    auto res = utils::fill_vector_with_sequence(to_copy, 27);

    for (const auto& e : res)
        std::cout << e << ' ';
    std::cout << '\n';
}