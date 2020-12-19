#include <iostream>
namespace solution1 {
bool isBigEndian() {
    union test {
        int a;
        char b;
    };


    union test test;
    test.a = 0x12345678;
    if(test.b == 0x78)  {
        return false;
    }
    return true;
}
}
namespace solution2 {
    // linux
    // 或者说是用于判断堆栈的增长方向的
bool isBigEndian() {
    int a{};
    int* b = new int{};

    return reinterpret_cast<unsigned long long>(&a) < reinterpret_cast<unsigned long long>(b);
}
}
int main() {
    std::cout << std::boolalpha << "1: " << solution1::isBigEndian() << '\n'
     << "2: " << solution2::isBigEndian() << '\n';
}