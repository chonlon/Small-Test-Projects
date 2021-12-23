#include <fmt/core.h>
#include <math.h>

int main() {
    using fmt::print;
    {
        print("============ inf ==============\n");
        print("double {}\n", std::numeric_limits<double>::infinity());
        print("int {}\n", std::numeric_limits<int>::infinity());
        print("uint32 {}\n", std::numeric_limits<uint32_t>::infinity());
        print("float {}\n", std::numeric_limits<float>::infinity());
    }

    {
        print("============ float =============\n");
        print(".3f: {:.3f}\n", M_PI);
        print("no limit: {}\n", M_PI);
    }

    {
        print("============ hex ==============\n");
        print("0x7fffffff: {:x}\n", 0x7fffffff);
        print("0xffffffff: {:x}\n", 0xffffffff);
        print("110: {:x}\n", 110);
        print("'a': {:x}\n", 'a');
    }

    {
        print("============ binary ==============\n");
        print("0x7fffffff: {:b}\n", 0x7fffffff);
        print("0xffffffff: {:b}\n", 0xffffffff);
        print("110: {:b}\n", 110);
        print("'a': {:b}\n", 'a');
    }
}