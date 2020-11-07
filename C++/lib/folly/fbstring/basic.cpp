#include <base.h>
#include <cstdint>
#include <folly/FBString.h>

int main() {
    constexpr int loop_time = 1000;

    // 不写成一个template函数啦, 方便调试

    {
        CaseMarker c{"std::string"};

        std::string s{'0'};
        s.reserve(10);

        c.printSub("push_back");
        for (size_t i = 0; i < loop_time; ++i) {
            if (s.size() == s.capacity()) {
                std::cout << s.size() << '\n';
                s.push_back('a');
            } else {
                s.push_back('b');
            }
        }

        c.printSub("copy operator in long");
        std::string s_copy1 = s;
        std::string_view s_v_toprint = std::string_view(s_copy1.c_str(), 100);
        std::cout << s_v_toprint << " ..." << '\n';

        s.clear();

        c.printSub("copy operator in short");
        s.append("short string");
        std::string s_copy2 = s;
        std::cout << s_copy2 << '\n';

        c.printSub("string_view operator");
        std::string_view s_v = s;
        std::cout << s_v << '\n';
        
        c.printSub("assign");
        s.assign(s.c_str() + 2, 5);
        std::cout << s << '\n';

        c.printSub("replace");
        s.replace(0, 20, s_copy1, 0, 10);
        std::cout << s << '\n';
    }


    {
        CaseMarker c{"fbstring"};

        folly::fbstring s{'0'};
        s.reserve(10);

        c.printSub("push_back");
        for (size_t i = 0; i < loop_time; ++i) {
            if (s.size() == s.capacity()) {
                std::cout << s.size() << '\n';
                s.push_back('a');
            } else {
                s.push_back('b');
            }
        }

        c.printSub("copy operator in long");
        folly::fbstring s_copy1 = s;
        std::string_view s_v_toprint = std::string_view(s_copy1.c_str(), 100);
        std::cout << s_v_toprint << " ..." << '\n';

        s.clear();

        c.printSub("copy operator in short");
        s.append("short string");
        folly::fbstring s_copy2 = s;
        std::cout << s_copy2 << '\n';

        c.printSub("string_view operator");
        std::string_view s_v = s;
        std::cout << s_v << '\n';
        
        c.printSub("assign");
        s.assign(s.c_str() + 2, 5);
        std::cout << s << '\n';

        c.printSub("replace");
        s.replace(0, 20, s_copy1, 0, 10);
        std::cout << s << '\n';
    }

    folly::fbstring ss{'a'};
    ss.clear();

    return 0;
}