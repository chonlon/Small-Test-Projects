#include <functional>
#include <iostream>
#include <string>

void print(int i, const std::string& s) {
    std::cout << i << ' ' << s << '\n';
}

auto ff = &print;
auto fff = print;
int main() {
    int i = 5;
    const auto f = [](const std::string& arg1, auto&& arg2) {
        print(arg2, arg1);
    };
    for(int i = 0; i < 1000000; ++i) {
        f("hello", 1);
        //print(1, "hello");
    }
    return 0;
}