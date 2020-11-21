#include <type_traits>
#include <tuple>
#include <vector>
#include <utility>
#include <iostream>

template <typename... args>
void print(args... a) {
    (std::cout << ... << a);
}

template <std::size_t I>
std::size_t _1_do() {
    std::cout << I << '\n';
    return I;
}

template <std::size_t... I>
size_t f(std::index_sequence<I...>) {
    print(_1_do<I>()...);
    return 0;
}

template<typename... Args>
size_t ff(Args...) {
    return f(std::index_sequence_for<Args...>{});
}


int main() {
    ff(1,1,1,1,1,1,1,1);
}