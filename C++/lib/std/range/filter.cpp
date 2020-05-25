// current compile command: g++-10 1.cpp
// -std=c++20

#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> ints{0, 1, 2, 3, 4, 5};
    auto even = [](int i) { return 1 == i % 2; };
    auto square = [](int i) { return i * i; };

    for (int i : ints | std::views::filter(even) |
             std::views::transform(square)) {
        std::cout << i << ' ';
    }
}