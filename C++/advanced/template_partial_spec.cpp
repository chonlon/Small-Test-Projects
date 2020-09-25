#include <iostream>
#include <type_traits>
// using partial specficition to have a sfinae.see https://stackoverflow.com/questions/87372/check-if-a-class-has-a-member-function-of-a-given-signature
template<typename T>
struct has_member_func : std::integral_constant<bool, false>
{
    
};

template <typename T, typename = decltype(declval<T>().func())>
using enable_if_has_func = T;
//
//
template<template<typename...> class TT, typename... Ts>
struct has_member_func<enable_if_has_func<TT<Ts...>>> : std::integral_constant<bool, true>
{
};

// template<typename T>
// struct has_member_func<enable_if_has_func<T>> : std::integral_constant<bool, true>
// {
// };
struct A
{
    void func() {}
};

struct B
{

};
template<typename = void>
struct C
{
    void func() {}
};

template<typename = void>
struct D
{
};

int main()
{
    // not good enough.
    std::cout << has_member_func<A>::value << ' ' << has_member_func<B>::value;
    std::cout << has_member_func<C<>>::value << ' ' << has_member_func<D<>>::value;
    return 0;
}