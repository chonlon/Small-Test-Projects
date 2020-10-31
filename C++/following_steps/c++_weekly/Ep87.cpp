#include <optional>
#include <iostream>

struct S
{
    S(const S&) = default;
    S(S&&) {
        std::cout << "optmized?\n";
    };

    // void operator=(S&&) {
    //     std::cout << "optmized?\n";
    // }

    S() = default;
};

int main() {
    std::optional<S> s;
    //s = S();
    s.emplace(S());

    return 0;
}
