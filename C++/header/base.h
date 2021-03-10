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

#define PRINT_INVOKED() std::cout << "was invoked: " << __FUNCTION__ << '\n';

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
    : std::conditional_t<std::is_scalar<T>::value ||
                             std::is_same<std::string, std::decay_t<T>>::value,
                         std::true_type,
                         std::false_type>
{};

template <typename FirstType, typename SecondType>
struct IsCoutable<std::pair<FirstType, SecondType>>
    : std::conditional_t<IsCoutable<FirstType>::value &&
                             IsCoutable<SecondType>::value,
                         std::true_type,
                         std::false_type>
{};


namespace print_container {
template <typename T, typename = std::enable_if_t<lon::IsCoutable<T>::value>>
inline auto operator<<(std::ostream& lhs, const std::vector<T>& is) -> std::ostream& {
    for (const auto& i : is) {
        lhs << i << '\n';
    }
    return lhs;
}
template <typename F,
          typename S,
          typename = std::enable_if_t<lon::IsCoutable<F>::value &&
                                      lon::IsCoutable<S>::value>>
inline auto operator<<(std::ostream& lhs, const std::pair<F, S>& is) -> std::ostream& {
    lhs << '[' << is.first << ',' << is.second << ']'
        << ' ';  // pair 就先不支持嵌套类型吧...
    return lhs;
}
}  // namespace print_container


template <typename ContainerType,
          typename Type = typename ContainerType::value_type,
          typename      = std::enable_if_t<lon::IsCoutable<Type>::value>>
inline void printContainer(const ContainerType& is, char divider = '\n') {
    using namespace lon::print_container;
    for (const auto& i : is) {
        std::cout << i << divider;
    }
}

// clang-format off
// vector嵌套其它container类, 需要的话, 后面可以定义其它container嵌套的情况..., 等有需要吧.
// PS: 如果需要实现无限制嵌套, 比如三层嵌套, 最简单的做法是在上面IsCoutable添加vector的特化, 这样vector自己可以通过printContainer的检查,而不用每次都对参数做函数重载,
// 不过这样有一个很尴尬的问题, 怎么才能对每层的vector提供不同的分隔符去区分它们呢,难道是使用args...,然后再不停解开参数包吗? 而且真的有实现的必要吗? 我觉得现在这样就可以了.
// clang-format on
template <typename ContainerType,
          typename Type = typename ContainerType::value_type,
          typename      = std::enable_if_t<lon::IsCoutable<Type>::value>>
inline void printContainer(const std::vector<ContainerType>& is,
                           char divider = '\n') {
    for (const auto& i : is) {
        printContainer(i, ' ');
        std::cout << divider;  // 相对来说还是这个版本满意一点..., 利用sfinae,
                               // vector<container>会进入这个函数,
                               // 单独vector<T>会进入上面那个函数.
    }
}
template <
    typename Type,
    typename = std::enable_if_t<lon::IsCoutable<std::decay_t<Type>>::value>>
inline void doPrint(Type&& v) {
    using namespace lon::print_container;
    std::cout << v;
}

template <typename ContainerType, typename = typename ContainerType::value_type>
inline void doPrint(const ContainerType &v)
{
    std::cout << '{';
    if(!v.empty()) {
        auto end_it  = v.end();
        --end_it;
        auto i = v.begin();
        for(; i != end_it; ++i)
        {
            doPrint(*i);
            std::cout << ',';
        }
        doPrint(*i);
    }

    std::cout << '}';
}

// template <typename ContainerType, typename = typename ContainerType::value_type>
// inline void doPrint(const ContainerType& v) {
//     for (const auto& i : v) {
//         doPrint(i);
//         std::cout << ' ';
//         // 还是不满意... 怎么针对多层使用不同的分隔符呢
//     }
//     std::cout << '\n';
// }

template <typename ContainerType, typename = typename ContainerType::value_type>
inline void doPrintContainer(const ContainerType& v) {
    doPrint(v);
    std::cout << '\n';
}
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
    int sub_counter_ = 0;
    std::string marker_;

public:
    CaseMarker() {
        // not use std::string_literals; cause it need cpp14.
        static int time = 0;
        time_           = ++time;
        printDividing(std::string("run case") + std::to_string(time_));
    }

    CaseMarker(const std::string& marker) : marker_{marker} {
        if (marker_.empty())
            throw std::invalid_argument{"marker should be not empty"};
        printDividing(std::string("run case ") + marker_);
    }

    void printSub(const std::string& sub_marker) {
        if (sub_marker.empty())
            throw std::invalid_argument{"sub_marker should be not empty"};
        std::cout << "--- " << ++sub_counter_ << ':' << sub_marker << " ---\n";
    }

    void printSub() {
        std::cout << "--- " << ++sub_counter_ << " ---\n";
    }

    ~CaseMarker() {
        if (marker_.empty())
            printDividing(std::string("end case") + std::to_string(time_));
        else
            printDividing(std::string("end case ") + marker_);
        std::cout << '\n';
    }
};
