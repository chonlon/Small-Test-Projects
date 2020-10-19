#include "../../header/base.h"
#include <iostream>
//see https://zh.cppreference.com/w/cpp/language/fold

template <typename ... T>
auto sum(T ... t) {
    return (t + ...);
}

template <typename ... T>
auto avg(T ... t) {
    return (t + ...) / sizeof...(t);
}

template <typename ... T>
auto div(T ... t) {
    const int i = 5;
    return ( i / ... / t );
}

template <typename ... T>
auto div2(T ... t) {
    const int i = 5;
    return (... / t) / i;
}

template <typename ... T>
void print(T ... t) {
    (std::cout << ... << t) << '\n';
}

int main() {
    {
        CaseMarker c{ "cals" };
        std::cout << sum(1, 1.2, 3, 4) << '\n';
        std::cout << avg(1.0, 2.0, 3.0, 4.0) << '\n';
        std::cout << div(1.0, 2.0, 3.0) << '\n';// rst = 5/1/2/3
        std::cout << div2(1.0, 2.0, 3.0) << '\n';// rst = 1/2/3/5.
    }

    {
        CaseMarker c{ "print" };
        print(1, 2, 3, "123");
    }
}
