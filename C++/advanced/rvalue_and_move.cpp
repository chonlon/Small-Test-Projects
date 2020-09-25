// g++ 1.cpp -fno-elide-constructors. && g++ 1.cpp to see differences.

#include <iostream>

using namespace std;

int g_constructCount = 0;

struct A
{
    /* data */
    A() {
        id = ++g_constructCount;
        cout << "construct: " << id << '\n';
    }

    A(const A&) {
        id = ++g_constructCount;
        cout << "copy construct: " << id << '\n';
    }
// test without this func
    A(A&&) {
        id = ++g_constructCount;
        cout << "move construct: " << id << '\n';
    }

    ~A() {
        cout << "destruct: " << id << '\n';
    }

    int id;
};

A getA() {
    return A{};
}

int main() {
    A a = getA();
    return 0;
}