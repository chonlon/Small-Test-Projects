#include <iostream>
#include <type_traits>
// check if a class has func.
// spefic name 'func'
// to have universal usage: you need macro.


struct A{
    void func(){}
};

struct B {

};

struct C
{
    void func(int) {}
};

struct class_has_func {
    template<typename T, typename... Args>
    static constexpr bool test(std::decay_t<(std::declval<T>().func(std::declval<Args...>()))>*) {
        return true;
    }

    template<typename T>
    static constexpr bool test(std::decay_t<(decltype(std::declval<T>().func())>*) {
        return true;
    }

    template<typename, typename>
    static constexpr bool test(...) {
        return false;
    }
};

template <typename T, typename... Args>
using has_func = typename std::conditional_t<class_has_func::template test<T, Args...>(nullptr), std::true_type, std::false_type>;



int main() {
    std::cout << has_func<A>::value << ' ' << has_func<B, int>::value  << ' ' << has_func<C, int>::value  << '\n';
}