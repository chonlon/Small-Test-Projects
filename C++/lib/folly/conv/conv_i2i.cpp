#include <folly/Conv.h>
#include <iostream>

template <typename T_To, typename T_From>
void conv_i2i(T_From f) {
    try
    {
        auto a = folly::to<T_To>(f);
    } catch (folly::ConversionError& e) {
        std::cerr << e.what() << " which from type is:" << typeid(T_From).name() <<'\n';
    }
}

int main() {
    short x;
    unsigned short y;
    long z;

    x = 123;
    conv_i2i<unsigned short>(x);
    x = -1;
    conv_i2i<unsigned short>(x);
    z = 2000000000;
    conv_i2i<int>(z);
    z += 1000000000;
    conv_i2i<int>(z);
    conv_i2i<unsigned int>(z);
    return 0;
}