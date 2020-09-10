#include <boost/algorithm/cxx11/none_of.hpp>
#include <boost/algorithm/cxx11/one_of.hpp>
#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};
    constexpr int    none = 0;
    constexpr int    one = 1;


    std::cout << std::boolalpha
        << std::none_of(std::begin(v),
                        std::end(v),
                        [&none](int i)
                        {
                            return i ==
                                none;
                        })
        << " "
        << boost::algorithm::none_of_equal(
            std::begin(v),
            std::end(v),
            none)
        << '\n';

    v.push_back(1);
    std::cout << "any of? "
        // stl no one of now.
        << std::any_of(std::begin(v),
                       std::end(v),
                       [&one](int i)
                       {
                           return i == one;
                       })
        << "\none of? "
        
        << boost::algorithm::one_of_equal(
               std::begin(v), std::end(v), one)
        << '\n';

    return 0;

}
