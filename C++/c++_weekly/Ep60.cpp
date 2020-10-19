#include <iostream>
#include <iomanip>

int main() {
    std::cout << std::quoted("Say \"Hello world!\"") << '\n';

    auto str = R"foo(Say "Hello world!")foo";

    std::cout << "native: " << std::quoted(str) << " print as: " << str << '\n';

}