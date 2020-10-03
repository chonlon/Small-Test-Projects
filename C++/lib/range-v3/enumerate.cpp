#include <range/v3/view/enumerate.hpp>
#include <range/v3/view/all.hpp>

#include <iostream>

int main() {
    std::vector<int> storedValues{1, 2, 3, 88, 99};
    for (auto const& [idx, value] :
         storedValues |
         ranges::view::enumerate) {
        std::cout << idx << ": " << value <<'\n';
    }
}
