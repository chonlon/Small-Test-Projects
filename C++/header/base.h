#pragma once
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <type_traits>
#include <vector>
///////////////////////////////////////////////
// micros
///////////////////////////////////////////////

#define PRINT_INVOKED() std::cout << "was invoked: " << __FUNCTION__;

///////////////////////////////////////////////
// functions
///////////////////////////////////////////////

void printDividing() {
    std::cout << "=======================================\n";
}

void printDividing(std::string&& s) {
    std::cout << "===================" << s << "====================\n";
}

namespace lon {
template <typename T>
struct IsCoutable
    : std::conditional_t<std::is_scalar<T>::value |
                             std::is_same<std::string, T>::value,
                         std::true_type,
                         std::false_type>
{};

template <typename ContainerType,
          typename Type = typename ContainerType::value_type,
          typename      = std::enable_if_t<lon::IsCoutable<Type>::value>>
inline void printContainer(const ContainerType& is, char divider = '\n') {
    for (const auto& i : is)
    {
        std::cout << i << divider;
    }
}


//像vector和list这样的模板类怎么再次作为模板参数呢?下面的做法还是会导致代码重复.

template <typename T, typename = std::enable_if_t<lon::IsCoutable<T>::value>>
inline void printVector(const std::vector<T>& is, char divider = '\n') {
    for (const auto& i : is)
    {
        std::cout << i << divider;
    }
}

template <typename T, typename = std::enable_if_t<lon::IsCoutable<T>::value>>
inline void printList(const std::list<T>& is, char divider = '\n') {
    for (const auto& i : is)
    {
        std::cout << i << divider;
    }
}

template <typename K,
          typename V,
          typename = std::enable_if_t<lon::IsCoutable<K>::value>,
          typename = std::enable_if_t<lon::IsCoutable<V>::value>>
inline void printMap(const std::map<K, V>& is, char divider = '\n') {
    for (const auto& i : is)
    {
        std::cout << i.first << ' ' << i.second << divider;
    }
}

namespace print_container {
template <typename T, typename = std::enable_if_t<lon::IsCoutable<T>::value>>
auto operator<<(std::ostream& lhs, const std::vector<T>& is) -> std::ostream& {
    for (const auto& i : is)
    {
        lhs << i << '\n';
    }
    return lhs;
}
}  // namespace print_container
}  // namespace lon


///////////////////////////////////////////////
// classes
///////////////////////////////////////////////

/// <summary> base field that count all this class construct time, and print
/// when construct and destruct </summary>
class BaseField
{
    int construct_time_;

    public:
    BaseField() {
        static int construct_time = 0;
        construct_time_           = ++construct_time;
        std::cout << "BaseField Ctor"
                  << "--" << construct_time_ << "\n";
    }

    ~BaseField() {
        std::cout << "BaseField Dtor"
                  << "--" << construct_time_ << "\n";
    }
};

/// <summary> an intfield that prints int</summary>
class IntField : public BaseField
{
    int var_;

    public:
    IntField(int _var) : var_(_var) {}

    void print() {
        std::cout << "Int Field:" << var_ << "\n";
    }
};


/**
 * \brief mark test case in output.
 */
class CaseMarker
{
    int time_;
    std::string marker_;

    public:
    CaseMarker() {
        // not use std::string_literals; cause it need cpp14.
        static int time = 0;
        time_           = ++time;
        printDividing(std::string("run case") + std::to_string(time_));
    }

    CaseMarker(const std::string& marker) : marker_{marker} {
        if (marker_.size() == 0)
            throw std::logic_error{"marker should be not empty"};
        printDividing(std::string("run case ") + marker_);
    }

    ~CaseMarker() {
        if (marker_.empty())
            printDividing(std::string("end case") + std::to_string(time_));
        else
            printDividing(std::string("end case ") + marker_);
        std::cout << '\n';
    }
};
