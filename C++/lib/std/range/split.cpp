// current compile command: g++-10 1.cpp
// -std=c++20

#include <iostream>
#include <ranges>
#include <vector>


int main() {
    std::vector<std::string> texts{
        "hello\nwe all know we can do it\nyes",
        "world",
        "bill",
        "holly"};

    auto filterY = [](const std::string& s) {
        return s.find_first_of('y') ==
            std::string::npos;
    };
    // todo fix here.
    std::string text = texts[0] |
        std::views::split('\n') |
        std::views::filter(filterY) |
        std::views::join("\n");
    std::cout << text << "\n";
    return 0;
}
