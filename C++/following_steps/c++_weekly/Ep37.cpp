#include <iostream>
#include <utility>

int main() {
    auto foo = [i = 0, j = 1]() mutable {
        i = std::exchange(j, j + i);
        return i;
    };
    
    for(int i = 0; i < 10; ++i) {
        foo();
    }
    
    std::cout << foo();
    
    return 0;
}