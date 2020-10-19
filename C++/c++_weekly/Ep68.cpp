#include <algorithm>
#include <array>
#include <iostream>
#include <numeric>
#include "../header/base.h"

int main() {
    std::array<int, 10> arr{};
    std::iota(std::begin(arr), std::end(arr), 0);

    lon::printContainer(arr, ' ');

    std::array<int, 10> arr_gen{};
    std::generate(std::begin(arr_gen), std::end(arr_gen), [i = 0]() mutable {
        ++i;
        return i * i;
    });

    lon::printContainer(arr_gen, ' ');

    return 0;
}