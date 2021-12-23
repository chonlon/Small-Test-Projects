#include <chrono>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/ranges.h>

int main() {
    fmt::print("======print=====\n");
    fmt::print("Hello, world!\n");
    fmt::print("==============\n\n");

    {
        fmt::print("\n================ basic format =======================\n");
        std::string s{"Hello, world"};
        float pi = 3.1415;
        fmt::print(fmt::format(
            "str: {}\nfloat: {}\ncstr: {}\nint: {}\nchar: {}\nuchar: {}\n",
            s,
            pi,
            "123456789",
            0xffff7777,
            static_cast<char>('a'),
            static_cast<u_char>('a')));
    }

    {
        fmt::print("\n================== chrono ======================\n");


        using namespace std::literals::chrono_literals;
        fmt::print("Default format: {} {}\n", 42s, 100ms);
        fmt::print("strftime-like format: {:%H:%M:%S}\n", 3h + 15min + 30s);
    }
    
    
    {
        std::vector<int> v = {1, 2, 3};
        fmt::print("{}\n", v);
    }
}