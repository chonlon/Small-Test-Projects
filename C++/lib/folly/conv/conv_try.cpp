#include <folly/Conv.h>
#include <iostream>
#include <string>

void doPrint(double d) {
    std::cout << __FUNCTION__ << ' ' << d << '\n';
}

int main() {
    std::string str = "1.112";
    folly::tryTo<double>(str).then([](double d) { doPrint(d); });
    str = "1.2.3.4";
    try
    {
        folly::tryTo<double>(str).thenOrThrow([](double d) { doPrint(d); });
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}