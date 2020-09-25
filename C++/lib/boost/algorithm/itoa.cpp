#include <iostream>
#include <boost/algorithm/cxx11/iota.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptors.hpp>
#include <vector>

int main() {
    std::vector<int> vec(10);
    boost::algorithm::iota(
        std::begin(vec),
        std::end(vec),
        1);
    for (const auto& i : vec) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    std::vector<int> vec2(10);
    boost::algorithm::iota(vec2, 10);
    for (const auto& i : vec2 |
         boost::adaptors::reversed) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    boost::algorithm::iota_n(
        std::back_inserter(vec),
        11,
        10);
    for (const auto& i : vec) {
        std::cout << i << ' ';
    }
}
