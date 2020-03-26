#include <vector>
#include <iostream>

int main() {
    try{
        for(;;)
            new std::vector<int>{1000000000};
    } catch(...) {
        std::cout << "error";
    }
}