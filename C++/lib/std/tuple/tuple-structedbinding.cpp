#include <tuple>
#include <iostream>
#include <string>
#include "../../../header/base.h"

auto foo() {
    return std::tuple{std::string{"hello"}, 1, 1.0};
}

int main() {
    auto [a, b, c] = foo();
    std::cout << typeid(a).name() << " " << typeid(b).name() << " " << typeid(c).name() << "\n";
    printDividing();
    std::cout << a << "\n" << b << "\n" << c;
}