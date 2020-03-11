#include <array>
#include <iostream>

template<int i>
struct t{
std::array <int, i> a;
static constexpr int len() {return i;}
};

int main() {
    std::array<int, 10> arr{1};
    for(auto i : arr) {
        
    }
    t<10> te;
    std::array<int, t<10>::len()> arr2{2};
    std::cout << arr2[0];
    return 0;
}