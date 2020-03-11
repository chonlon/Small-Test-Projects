#include <iostream>
#include <functional>
#include "../../../header/base.h"

void print(int a) {
    std::cout << __FUNCTION__ << " " << a << std::endl;
}

void print2(int a, int b) {
    std::cout << __FUNCTION__ << " " << a << " " << b << std::endl;
}

template <typename F, typename... Args>
void viazz(F&& a, Args... arg) {
    // 1. 如何传递args.
    // 2. F到底是函数指针还是什么.- folly future中的args是需要上一个future传递的.
    // 3. 如何使用SFINAE来使如果F不是函数指针类型就不调用.
    std::cout << "嘿嘿嘿, 成功了" << std::endl;
}

template <typename F, typename... Args>
std::enable_if_t<std::is_invocable_v<F, Args...>, std::invoke_result_t<F, Args...>>
via(F a, Args&&... arg) {
    return a(std::forward<Args>(arg...));
}

void via(...) {
    std::cout << "嘿嘿嘿, 成功了" << std::endl;
}

template <typename R, typename... Args>
void via2(R (&func)(Args...)) {
    func(1);
}

// 这里一开始比较困惑的就是...的写法了, 需要在typename中加..., 可以看做...不属于Args类型的一部分,也不属于实参a的一部分. 
template <typename R, typename... Args>
void via3(R (&func)(Args...), Args&&... a) {
    func(std::forward<Args>(a)...);
}

// 这个函数的调用可以和上面使用右值的写法做一个对比.
template <typename R, typename... Args>
void via4(R (&func)(Args...), Args... a) {
    std::cout << "is same? : " << std::boolalpha << std::is_same<R, std::invoke_result_t<decltype(func), Args...>>::value;
    // 不能写作: func(a);
    func(a...);
}

int main() {
    auto p = &print;
    via(p, 1);
    printDividing();
    via(1, 1);
    printDividing();
    //via2(p); //error
    via2(print);
    via3(print, 1);
    // todo how to use args.. to invoke function.
    via3(print2, 8, 2);
    via4(print2, 5, 6);
    return 0;
}