#include <type_traits>
#include <iostream>

template <typename T1, typename T2>
std::common_type_t<T1, T2> max(T1 a, T2 b)
{
    return a > b ? a : b;
}

template <typename T1, typename T2> 
auto max_a(T1 a, T2 b) -> std::decay_t<decltype(true ? std::declval<T1>() : std::declval<T2>())> // 这里返回类型推导如果不使用decay_t外包可能会有引用类型错误.
{
    return a > b ? a : b;
}



int main()
{
    auto a = ::max(12, 2.0);
    auto b = ::max(1, 2);

    auto c = ::max_a(1, 2);

    std::cout << typeid(a).name() << ' ' << typeid(b).name() << '\n';

    std::cout << typeid(c).name() << '\n';

    return 0;
}