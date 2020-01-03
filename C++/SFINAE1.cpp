#include <functional>
#include <iostream>

template <typename F, typename... Args>
using resultOf = decltype(std::declval<F>()(std::declval<Args>()...));

template <typename F, typename... Args>
struct callableWith
{
    template <typename T,
              typename = resultOf<T, Args...>>
    static constexpr std::true_type
        check(std::nullptr_t) { return std::true_type{}; };

    template <typename>
    static constexpr std::false_type
    check(...) { return std::false_type{}; };

    typedef decltype(check<F>(nullptr)) type;
    static constexpr bool value = type::value;
};

template<typename = int>
void ff(int a) {
    std::cout << "int function";
}

template <typename>
void ff(...)
{
    std::cout << "other function";
}

int f(int a) { return 1; }

int main()
{
    auto a = f;
    std::cout << std::boolalpha << callableWith<decltype(a), int>{}.value << " "
              << callableWith<decltype(a), void>{}.value;


    ff(9.0);
}
