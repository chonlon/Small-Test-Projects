#include <memory>
template<typename T, typename... Args>
T ct(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

// test below...
struct A{
    int a;
    A(int _a) : a(_a) {};
};
#include <iostream>
int main() {
    auto t = ct<A>(3);
    std::cout << t.a;
}