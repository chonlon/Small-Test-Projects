#include <iostream>
#include <string>

int main() {
    std::string s;
    char buf[1024]{0};
    while(std::cin.getline(buf, 1024)) {
        std::cout << buf << '\n';
    }
    return 0;
}