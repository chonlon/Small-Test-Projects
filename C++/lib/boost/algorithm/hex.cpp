#include <boost/algorithm/hex.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace boost;
int main() {
    //std::string s(1, ' ');
    //std::vector<int> v(10);
    //algorithm::unhex("616263646566", std::ostream_iterator<int>(std::cout));
    algorithm::hex("123aabvb", std::ostream_iterator<int>(std::cout));
    //algorithm::unhex("32", v.begin() + 1);
    //std::cout << s << ' ' << v[0] << '\n';
    return 0;
}