#include <boost/algorithm/clamp.hpp>
#include <boost/range.hpp>
#include <vector>
#include <iostream>
#include "../../../header/base.h"

int main() {
    constexpr int left = 10;
    constexpr int right = 100;
    using boost::algorithm::clamp;
    using boost::algorithm::clamp_range;

    {
        CaseMarker c;
        std::cout << clamp(1, left, right) << ' '
            << clamp(11, left, right) << ' '
            << clamp(101, left, right) << '\n';
    }

    {
        CaseMarker       c;
        std::vector<int> vals{0, 1, 9, 10, 11, 28,
                              39, 78, 99, 100,
                              101, 102};
        std::vector<int> results;
        clamp_range(vals, std::back_inserter(results), left, right);
        for (const auto &i : results) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
