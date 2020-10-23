#include "TestClasses.hpp"

int main(int argc, char** argv) {
    MultiInherit m;
    m.foo();
    return sizeof(MultiInherit);
}