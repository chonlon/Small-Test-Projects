#include <boost/algorithm/cxx11/is_sorted.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    std::vector<int> incr;
    std::vector<int> decr;
    std::cout << std::boolalpha;
    
    {
        std::vector<int> s_decr{4, 3, 2, 1};
        std::vector<int> s_incr{1, 2, 3, 4};

        auto s_decr_begin = std::begin(s_decr);
        auto s_decr_end = std::end(s_decr);
        auto s_incr_begin = std::begin(s_incr);
        auto s_incr_end = std::end(s_incr);

        // stl has no strctly version.
        // in vc once you pass lambda like [](int lhs, int rhs) { return lhs >= rhs; } you will get a invalid comparator expection.
        // in g++ you will get wrong result.
        std::cout << "strictly decr? "
            << "std:"
            << std::is_sorted(
                s_decr_begin,
                s_decr_end,
                [](int lhs, int rhs)
                {
                    return lhs > rhs;
                })
            << " boost:"
            << boost::algorithm::is_strictly_decreasing(
                s_decr_begin,
                s_decr_end)
            << "\nstrictly incr? "
            << "std:"
            << std::is_sorted(
                s_incr_begin,
                s_incr_end,
                [](int lhs, int rhs)
                {
                    return rhs < lhs;
                })
            << " boost:"
            << boost::algorithm::
            is_strictly_decreasing(
                s_incr_begin,
                s_incr_end)
            << "\n";

        incr = std::move(s_incr);
        decr = std::move(s_decr);
    }


    {
        incr.push_back(4);
        decr.push_back(1);
        auto decr_begin = std::begin(decr);
        auto decr_end = std::end(decr);
        auto incr_begin = std::begin(incr);
        auto incr_end = std::end(incr);

        std::cout << "decr? "
            << "std:"
            << std::is_sorted(
                decr_begin,
                decr_end,
                [](int lhs, int rhs)
                {
                    return lhs > rhs;
                })
            << " boost:"
            << boost::algorithm::is_decreasing(
                decr_begin,
                decr_end)
            << "\nincr? "
            << std::is_sorted(incr_begin, incr_end, [](int lhs, int rhs){return lhs < rhs;})
            << ' '
            << boost::algorithm::is_increasing(
                incr_begin,
                incr_end);
#ifdef  __GNUC__
        auto iter = std::is_sorted_until(decr_begin, decr_end, [](int lhs, int rhs) {
            return lhs <= rhs;
        });
        std::cout<< '\n' << iter - decr_begin;
#endif
    }

}
