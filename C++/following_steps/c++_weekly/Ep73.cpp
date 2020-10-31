#include <string_view>
#include <string>
#include <iostream>
#include <algorithm>


int main() {
    std::string s(20, '*');

    s.append(20, '+');
    
    auto first = std::find(std::begin(s), std::end(s), '+');
    
    // c++20; g++-10 Ep73.cpp -std=c++20.
    std::string_view mul_view = std::string_view(std::begin(s), first);
    std::string_view plus_view = std::string_view(first, std::end(s));

    //std::string mul_view = std::string(begin(s), first);
    
    //s.~basic_string<char>();手动调用析构以后string_viwe里的数据也会被释放. 也就是: string_view不管理内存.
    std::cout << std::boolalpha << (mul_view.data() == s.data()) << '\n';
    std::cout << s.data() - plus_view.data() << '\n';
    std::cout << "1: " << mul_view << "\n2: " << plus_view << '\n';
}