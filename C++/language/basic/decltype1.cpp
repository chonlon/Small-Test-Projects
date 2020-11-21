#include "../header/base.h"
#include <iostream>
#include <utility>

struct Default {
    int foo() const {
        PRINT_INVOKED();
        return 1;
    }
};

struct NonDefault {
    NonDefault() = delete;// make it clearer that defalut consturctor was deleted.
    NonDefault(const NonDefault&) {}
    int foo() const {
        PRINT_INVOKED();
        return 1;
    }
};

int main() {
    decltype(Default().foo()) n1 = 1;  // type of n1 is int
    std::cout << typeid(n1).name() << "\n";
    printDividing();
    decltype(std::declval<NonDefault>().foo()) n2 = n1;  // type of n2 is int
    std::cout << typeid(n2).name() << "\n";
    printDividing();
    std::cout << "n1 = " << n1 << '\n'
              << "n2 = " << n2 << '\n';
}