#include <numeric>
#include <iostream>

int main() {
    std::cout << "constexpr that cal gcd at complile time: " << std::gcd(21, 14) <<  '\n';

    int a = 23;
    int b = 3;

    std::cout << "run time var cal lcm: " << std::lcm(a, b) << '\n';
    return 0;
}