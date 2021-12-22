#include <fmt/core.h>

int main() {
    fmt::print("======print=====\n");
    fmt::print("Hello, world!\n");
    fmt::print("==============\n\n");

    {
        fmt::print("\n================ basic format =======================\n");
        std::string s{"Hello, world"};
        float pi = 3.1415;
        fmt::print(fmt::format("str: {}\nfloat: {}\ncstr: {}\nint: {}\nchar: {}\nuchar: {}\n",s,pi,"123456789",0xffff7777,static_cast<char>('a'), static_cast<u_char>('a')));
    }
}