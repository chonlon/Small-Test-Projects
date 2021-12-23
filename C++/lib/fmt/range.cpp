#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/ranges.h>

#include <vector>
#include <set>
#include <map>

void printCase(const char* name) {
    fmt::print("=========== ");
    fmt::print(fg(fmt::color::red), "{}", name);
    fmt::print(" ===========\n");
}

int main() {
    std::vector<std::set<int>> vecs{{1, 2, 3}, {2, 3, 4}, {4, 5, 6}};
    std::map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
    std::tuple<int, std::map<int,std::string>, float> tup{1, map, 1.111};

    printCase("r1");
    fmt::print("vector set: {}\n", vecs);
    fmt::print("map: {}\n", map);
    fmt::print("tup: {}\n", tup);

    printCase("r2");
    fmt::print("vector set: {}\n", fmt::join(vecs, " "));
    fmt::print("map:\n\t{}\n", fmt::join(map, "\n\t"));
    fmt::print("tup: {}\n",  fmt::join(tup, " | "));

    printCase("r3");
}