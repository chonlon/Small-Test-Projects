#include <iostream>

class base1 {
public:
    base1() = default;
    virtual void print() {std::cout << 1 << "\n";}
};

class base2 : public base1{
public:
    base2() = default;
    void print() override {std::cout << 2 << "\n";}
};

class base3 : public base2{
    int a = 100;
public:
    base3() = default;
    void print() override {std::cout << 3 << "\n";}
    void nValaidFunc() { std:: cout << a << "\n";}
};

int main() {
    base1* ptr = new base3;

    auto s_p = static_cast<base2*>(ptr);
    auto r_p = dynamic_cast<base2*>(ptr);

    if(s_p) {
        s_p->print();
    }

    if(r_p) {
        r_p->print();
    }

    base1* ptr2 = new base2;
    auto s_p2 = static_cast<base3*>(ptr2);
    auto r_p2 = dynamic_cast<base3*>(ptr2);

    if(s_p2) {
        s_p2->print();
        s_p2->nValaidFunc();
    }

    if(r_p2) {
        r_p2->print();
    } else {
        std::cout << "\n" << "null cast" << __LINE__ << "\n";
    }

    return 0;
}