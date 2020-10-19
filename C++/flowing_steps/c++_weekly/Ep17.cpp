#include <functional>
#include <iostream>

int doSomething(const int i) {
    return i;
}

struct S {
    int j = 5;
    int doSomething(const int i) {
        return j + i;
    }
};

int main() {
    std::cout << std::invoke(doSomething, 5) << '\n';
    S s;
    std::cout << std::invoke(&S::doSomething, &s, 3) << '\n';
}