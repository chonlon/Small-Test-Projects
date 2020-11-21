#include <iostream>

// test if constexpr
// g++ -std=c++11 if_constexpr.cpp 将会得到一个错误. 原因是直接的if else不是编译期的, 所以NonePolymorphic不能通过编译期检查.


class Polymorphic {
public:
    virtual Polymorphic clone() {
        std::cout << "clone\n";
        return Polymorphic{};
    }
};


class NonePolymorphic {
public:
    NonePolymorphic() = default;
    NonePolymorphic(const NonePolymorphic& np) {
        std::cout << "copy\n";
    }
};

template <typename T, bool isPolymorphic>
class Test {
public:
    void DoSomething(T& t) {
// c++17
#if __cplusplus == 201703
        if constexpr (isPolymorphic) {
            t.clone();
        } else {
            T{t};
        }
// c++11
#else
        if (isPolymorphic) {
            t.clone();
        } else {
            T{t};
        }
#endif
    }
};

int main() {
    std::cout << __cplusplus << '\n';


    Polymorphic p;
    Test<Polymorphic, true>{}.DoSomething(p);

    NonePolymorphic np;
    Test<NonePolymorphic, false>{}.DoSomething(
        np);

    return 0;
}