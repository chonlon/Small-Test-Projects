#include <range/v3/range.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/all.hpp>
#include <range/v3/view/transform.hpp>
#include <iostream> 
#include <vector>

auto is_odd = [](int i) {return i % 2 == 1;};


int main() {
    std::cout << ranges::view::all(ranges::view::iota(1, 100) | ranges::view::filter(is_odd) | ranges::view::transform([](int i){return i * i;}));
    
}


// #include <iostream>
// #include <vector>
//
// #include <range/v3/range/conversion.hpp>
// #include <range/v3/view/for_each.hpp>
// #include <range/v3/view/iota.hpp>
// #include <range/v3/view/repeat_n.hpp>
// using std::cout;
//
// int main()
// {
//     using namespace ranges;
//     auto vi = views::for_each(views::ints(1, 6),
//         [](int i) { return yield_from(views::repeat_n(i, i)); }) |
//         to<std::vector>();
//     // prints: [1,2,2,3,3,3,4,4,4,4,5,5,5,5,5]
//     cout << views::all(vi) << '\n';
// }