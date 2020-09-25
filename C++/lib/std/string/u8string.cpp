#define _GLIBCXX_USE_CHAR8_T 1

#include <string>
#include <iostream>
int main() {
    std::string c8str = "这是中文";

    std::u8string u8str = u8"这是中文";
    auto c1 = u8str[1];
    auto c2 = u8str[2];

    std::cout << c8str;
    //std::basic_ostream<char8_t> << u8str;
    std::cout << c8str.length() << ' ' << u8str.length();
}