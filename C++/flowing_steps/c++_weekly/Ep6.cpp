#include <iostream>
#include <sstream>
#include <vector>

#if 0
template <typename T>
std::string to_string_impl(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::vector<std::string> to_string() {
    return {};
}

template <typename P1, typename... Param>
std::vector<std::string> to_string(const P1& p1, const Param& ... param) {
    std::vector<std::string> ret;
    
    ret.push_back(to_string_impl(p1));
    auto rest = to_string(param...);
    ret.insert(ret.end(), rest.begin(), rest.end());
    
    return ret;
}
#else
template <typename T>
std::string to_string_for_one(const T& t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

void to_string_impl(std::vector<std::string>& ss) { // 终结递归
}

template <typename P1, typename... Param>
void to_string_impl(std::vector<std::string>& ss, const P1& p1, const Param& ... param) {
    ss.push_back(to_string_for_one(p1));
    to_string_impl(ss, param...); // 递归展开
}

template <typename... Param>
std::vector<std::string> to_string(const Param& ... param) {
    std::vector<std::string> ret;

    to_string_impl(ret, param...); // 参数展开

    return ret;
}
#endif

int main() {
    auto vec = to_string("hello", 1, 5.3);
    for (const auto& o : vec) {
        std::cout << o << '\n';
    }
}