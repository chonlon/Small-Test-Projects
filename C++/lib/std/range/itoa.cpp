// current compile command: g++-10 1.cpp
// -std=c++20

#include <iostream>
#include <ranges>
#include <vector>

int main() {
    for (long long i : std::views::iota(1, 100)) {
        std::cout << i << ' ';
    }
}
