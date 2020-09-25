#include <boost/algorithm/is_palindrome.hpp>
#include <vector>
#include <iostream>
// ╩ьнд.

int main() {
    std::vector<int> vec{1, 2, 3, 3, 2, 1};
    std::cout << std::boolalpha <<
        boost::algorithm::is_palindrome(
            vec.begin(),
            vec.end());
    vec.push_back(1);
    std::cout << '\n';
    std::cout << std::boolalpha
        << boost::algorithm::is_palindrome(
            vec.begin(),
            vec.end());
    return 0;
}
