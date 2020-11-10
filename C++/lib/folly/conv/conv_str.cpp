#include <base.h>
#include <folly/Conv.h>
#include <folly/FBString.h>
#include <iostream>
#include <string>

// 很像boost的lexical_cast

int main() {
    using namespace folly;
    {
        CaseMarker c{"to string"};
        auto a = to<fbstring>(123);
        std::cout << a << '\n';
        a = to<std::string>(-456);
        std::cout << a << '\n';
    }

    {
        CaseMarker c{"to int"};
        fbstring str = "  12345  ";
        std::cout << to<int>(str) << '\n';
        str = "  12345six seven eight";
        StringPiece pc(str);
        std::cout << to<int>(&pc) << " str: " << pc << '\n';
    }

    {
        CaseMarker c{"floating pointer"};

        fbstring str = "nan";
        double d     = to<double>(str);
        std::cout << "isnan: " << std::boolalpha << std::isnan(d) << '\n';
        str = "inf";
        d   = to<double>(str);
        std::cout << "isinf:" << std::isinf(d) << '\n';

        str = "1.11";
        std::cout << "conv to double: " << to<double>(str) << '\n';
    }

    return 0;
}