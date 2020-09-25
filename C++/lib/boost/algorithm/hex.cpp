#include <boost/algorithm/hex.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace boost;

int main() {
    //std::string s(1, ' ');
    std::vector<char> v;

    algorithm::hex("123aabvb",
                   std::ostream_iterator<int>(
                       std::cout));
    std::cout << '\n';
    algorithm::hex("32", std::back_inserter(v));
    for (const auto& i : v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    algorithm::unhex(
        "616263646566",
        std::ostream_iterator<char>(std::cout));
    try {
        algorithm::unhex("616263646566",
                         std::ostream_iterator<int
                         >(std::cout));
    } catch (const std::exception& e) {
        std::cout << e.what();
    }

    //std::cout << s << ' ' << v[0] << '\n';
    return 0;
}
