#include <folly/small_vector.h>
#include <base.h>

int main() {
    constexpr int size = 4;
    folly::small_vector<int, size> vec{{1,2,3,4}};
    std::cout << std::hex;
    printDividing("on stack");
    std::cout << reinterpret_cast<long>(&vec[0]) << '\n';
    printDividing("on heap");
    vec.push_back(1);
    std::cout << reinterpret_cast<long>(&vec[0]) << '\n';
}