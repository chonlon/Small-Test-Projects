#include "list.hpp"

#include <iostream>

struct T
{
    T() = default;

    explicit T(int a)
        : a{a} {
    }

    T(const T& other)
        : a(other.a) {
    }

    T(T&& other) noexcept
        : a(other.a) {
    }

    auto operator=(const T& other) -> T& {
        if (this == &other)
            return *this;
        a = other.a;
        return *this;
    }

    auto operator=(T&& other) noexcept -> T& {
        if (this == &other)
            return *this;
        a = other.a;
        return *this;
    }

    int a = 0;
};

std::ostream& operator<<(std::ostream& out, const T& rhs) {
    out << rhs.a;
    return out;
}

int main() {
    using namespace lon;
    List<T> list;

    T t;

    list.emplace_back(t);
    list.emplace_back(1);
    list.push_back(T(1));

    std::cout << list.size() << '\n';
    for (const auto& i : list) {
        std::cout << i << '\n';
    }

    return 0;
}