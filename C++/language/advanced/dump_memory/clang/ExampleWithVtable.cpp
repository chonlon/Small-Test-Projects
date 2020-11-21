#include "TestClasses.hpp"

void test(SimpleInherit* p) {
    p->foo();
}

void test(Base* p) {
    p->foo();
}

int main(int argc, char** argv) {
    return sizeof(SimpleInherit);
}