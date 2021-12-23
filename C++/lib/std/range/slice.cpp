#include <ranges>
#include <iostream>

int main() {
    auto ints = std::ranges::views::iota(10, 100);

    auto slice = ints | std::ranges::views::take(80) | std::ranges::views::drop(10);

    std::string str = "==================|||||aksdljfkl;asdjfkla;sjdf;lkajsdf";
    auto str_slice = str | std::ranges::views::take(30) | std::ranges::views::drop(10);

    for(auto i : slice) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    for(auto i : str_slice) {
        std::cout << i;
    }
//    std::cout << str_slice << std::endl;
}