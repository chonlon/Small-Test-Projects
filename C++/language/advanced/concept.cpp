#include <type_traits>
#include <iostream>
#include <vector>

template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept Floatpoint = std::is_floating_point_v<T>;

// template<Floatpoint T>
// T add(T a, T b)
// {
//     return a + b;
// }

// template <typename T>
// T add(T a, T b)
// {
//     return a + b;
// }

template <typename T>
requires Integral<T>
T add(T a, T b)
{
    return a + b;
}
template<typename  T>
T add_before(T a, T b)
{
    return a + b;
}


template<typename  T, typename = std::enable_if_t<std::is_integral_v<T>>>
T add_before(T a, T b)
{
    return a + b;
}



template <Integral T>
class my_class
{
public:
    void foo(T a)
    {
        std::cout << a;
    }
    
};


int main()
{
    std::cout << add(1, 1);
    //std::cout << add(1.1, 1.2);

    std::cout << add_before(1, 2);
    //std::cout << add_before(1.1, 1.2);
    return 0;
}