#include <iostream>
#include <vector>
#include <string>
#include <string_view>

int main() {
    std::vector<std::string> args = {"hello", "world"};
    std::string_view program_name = args[0];
    std::cout << "Program name: " << program_name << std::endl;
    std::cout << "Arguments: " << std::endl;
    for (int i = 1; i < args.size(); i++) {
        std::cout << args[i] << std::endl;
    }
}