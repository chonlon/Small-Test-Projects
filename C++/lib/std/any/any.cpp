#include <string>
#include <iostream>
#include <any>
#include <utility>

int main()
{
    // 简单示例

    auto a = std::any(12);

    std::cout << std::any_cast<int>(a) << '\n';

    try {
        std::cout << std::any_cast<std::string>(a) << '\n';
    }
    catch (const std::bad_any_cast& e) {
        std::cout << e.what() << '\n';
    }

    // 指针示例

    if (int* i = std::any_cast<int>(&a)) {
        std::cout << "a is int: " << *i << '\n';
    }
    else if (std::string* s = std::any_cast<std::string>(&a)) {
        std::cout << "a is std::string: " << *s << '\n';
    }
    else {
        std::cout << "a is another type or unset\n";
    }

    // 进阶示例

    a = std::string("hello");

    auto& ra = std::any_cast<std::string&>(a); //< 引用
    ra[1] = 'o';

    std::cout << "a: "
        << std::any_cast<const std::string&>(a) << '\n'; //< const 引用

    auto b = std::any_cast<std::string&&>(std::move(a)); //< 右值引用

    // 注意： 'b' 是移动构造的 std::string ， 'a' 被置于合法但未指定的状态

    std::cout << "a: " << *std::any_cast<std::string>(&a) //< 指针
        << "b: " << b << '\n';
}