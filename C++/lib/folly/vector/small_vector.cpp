#include <folly/small_vector.h>
#include <base.h>

int main() {
    [[maybe_unused]] folly::small_vector<int, 3> _vec{{1, 2, 3}};
    

    constexpr int size = 4;

    folly::small_vector<int, size> vec{{1,2,3}};
    
    std::cout << std::hex;
    printDividing("on stack");
    std::cout << reinterpret_cast<long>(&vec[0]) << '\n';
    vec.push_back(4);
    printDividing("on heap");
    vec.push_back(5);
    std::cout << reinterpret_cast<long>(&vec[0]) << '\n';
}