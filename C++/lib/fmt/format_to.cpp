#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h>
#include <iostream>
#include <iterator>
#include <fmt/ranges.h>

#include <vector>
#include <set>
#include <map>
#include <fstream>

struct Test {
    char msg[4]{'T','E','S','T'};
    int i = 0xfffffff;
    float f = 0.123456;
} __attribute__((packed));

int main() {
    auto formatTo = [](auto iter) {
        fmt::format_to(iter, "============ basic ============\n");
        fmt::format_to(iter, "{}\n", "Hello World!");

        fmt::format_to(iter, "============ num ==============\n");
        fmt::format_to(iter, "0x7fffffff: {:x}\n", 0x7fffffff);
        fmt::format_to(iter, "0xffffffff: {:x}\n", 0xffffffff);
        fmt::format_to(iter, "110: {:x}\n", 110);
        fmt::format_to(iter, "'a': {:x}\n", 'a');

        fmt::format_to(iter, "============ range ============\n");
        std::vector<std::set<int>> vecs{{1, 2, 3}, {2, 3, 4}, {4, 5, 6}};
        std::map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
        std::tuple<int, std::map<int,std::string>, float> tup{1, map, 1.111};

        fmt::format_to(iter, "vector set: {}\n", fmt::join(vecs, " "));
        fmt::format_to(iter, "map:\n\t{}\n", fmt::join(map, "\n\t"));
        fmt::format_to(iter, "tup: {}\n",  fmt::join(tup, " | "));

        fmt::format_to(iter, "============== raw struct ================\n");
        Test test;
        fmt::format_to(iter, "data: {}\n", std::string_view{reinterpret_cast<char*>(&test), sizeof(Test)});

        fmt::format_to(iter, "\n---end---\n");
    };


    formatTo(std::ostream_iterator<char>(std::cout));

    {
        std::string rst;
        formatTo(std::back_inserter(rst));
        fmt::print("\n======== str =============\n{}\n", rst);
    }
    
    {
        std::ofstream format_rst{"format_rst.txt", std::ios::trunc};
        formatTo(std::ostream_iterator<char>(format_rst));
    }
    
    
}