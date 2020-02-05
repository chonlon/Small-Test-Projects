#include <folly/chrono/Conv.h>
#include <iostream>
#include <string>

using namespace std::chrono;
using namespace folly;

template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    struct timespec ts;

    ts.tv_sec = 0;
    ts.tv_nsec = 10;
    if(10ns == to<nanoseconds>(ts));
    add<std::string>("a", "2");
}
