#include <iostream>
#include <exception>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <hash_map>
using namespace std;

template <typename T, typename U>
decltype(std::declval<T>() + std::declval<U>()) add_s(T p1, T p2, std::true_type)
{
    return p1 + p2;
}

template <typename T, typename U>
void add_s(T p1, T p2, std::false_type)
{
    throw std::logic_error{ "param is not addable" };
}

//template <class T, class U>
//struct is_addable_impl
//{
//    static auto check(T*, U*) -> decltype(std::declval<T>() + std::declval<U>(), std::true_type());
//
//    static auto check(...)->std::false_type;
//
//    typedef decltype(check(nullptr, nullptr)) type;
//};
//
//template <class T, class U>
//struct is_addable : decltype(is_addable_impl<T,U>::check(nullptr, nullptr)) {};

struct is_addable_impl
{
    template <class T, class U>
    static auto check(T*, U*) -> decltype(std::declval<T>() + std::declval<U>(), std::true_type());

    template <class T, class U>
    static auto check(...) -> std::false_type;
};

template <class T, class U>
struct is_addable : decltype(is_addable_impl::check<T, U>(nullptr, nullptr)) {};



template <typename T, typename U>
decltype(std::declval<T>() + std::declval<U>()) add(T p1, U p2)
{
    // arg..
    std::cout << typeid(T).name() << typeid(U).name() << std::endl;
    return 1.0;
    //return add_s(p1, p2, is_addable<T, U>::value);
}

int main()
{
    __gnu_cxx::hash_map<int, int> map;
    std::cout << add(1, 2) << " 1\n"
        << add(1.3, 1.2) << " 2\n"
        << std::endl;
    try
    {
        //add("2", "1");
    }
    catch (const std::exception & e)
    {
        std::cout << "Caught exception \"" << e.what() << "\"\n";
    }

    return 0;
}