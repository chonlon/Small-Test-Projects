#include <range/v3/all.hpp> // #include <ranges> in c++20
#include <iostream>
#include <vector>
#include <string>
using namespace std;
namespace vw = ranges::views; // std::views in c++20

string convert(string str, int n) {
    vector<string> vec(n);
    auto chars = str | vw::all;
    auto index = vw::concat(vw::iota(0, n), vw::iota(1, n - 1) | vw::reverse) | vw::cycle;
    for (auto&& [i, c] : vw::zip(index, chars)) {
        vec[i].push_back(c);
    }
    return vec | vw::join("") | ranges::to<string>;
}

int main() {
    string s = convert(string("LEETCODEISHIRING"), 4);
    cout << s << "\n"; // should output LDREOEIIECIHNTSG
    return 0;
}