#include <functional>
#include <iostream>
#include <string>

void print(int i, const std::string& s) {
    std::cout << i << ' ' << s <<  '\n';
}

int main() {
    int i = 5;
    const auto f = std::bind(print, std::placeholders::_2, std::placeholders::_1);
    for (int i = 0; i < 1000000; ++i) {
        f("hello", 1);
    }
    
    return 0;
}
