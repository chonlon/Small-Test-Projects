#include <folly/Demangle.h>
#include <string>
#include <iostream>
#include <typeinfo>
#include "demangle.h"

struct TestStruct {
    int a;
    std::string s;
};

int main() {
    int i;
    TestStruct test;
    std::cout << folly::demangle(typeid(i)) << ' ' << folly::demangle(typeid(test)) << '\n';

    std::cout << typeid(i).name() << ' ' << typeid(test).name() << '\n';
}