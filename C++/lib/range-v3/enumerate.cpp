#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/all.hpp>

#include <iostream>
#include <range/v3/view/iota.hpp>


int main()
{
    std::vector<int> storedValues{1, 2, 3, 88, 99};
    for (auto const& [idx, value] :
         storedValues |
         ranges::views::enumerate) {
        std::cout << idx << ": " << value << '\n';
    }

    std::cout << std::string(20, '*') << '\n';

    for (auto const& [idx, value] : ranges::views::iota(2, 20) |
         ranges::views::enumerate) {
        std::cout << idx << ": " << value << '\n';
    }
}
