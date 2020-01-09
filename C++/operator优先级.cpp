#include <iostream>

int main() {
    int *p = new int[3]{1, 4, 6};
    p++;
    std::cout << *p;
}