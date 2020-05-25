// current compile command: g++-10 1.cpp
// -std=c++20

// access index and use for range loop.
// at least it is more safe.

#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> storedValues{
        1, 2, 3, 88, 99};
    // for (auto const& [idx, value] :
    // storedValues |
    //          std::ranges::view::enumerate) {
    //     std::cout << idx << ": " << value <<
    //     '\n';
    // }

    for (size_t idx = 0;
         auto   value : storedValues) {
        std::cout << idx << ": " << value << '\n';
        ++idx;
    }
}
