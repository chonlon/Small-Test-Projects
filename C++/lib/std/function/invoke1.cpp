#include <functional>
#include <iostream>

struct Fn {
  char operator()(int, int) noexcept {
    return 'a';
  }
  int volatile&& operator()(int, char const*) {
    return std::move(x_);
  }
  float operator()(float, float) {
    return 3.14;
  }
  int volatile x_ = 17;
};


int main() {
    Fn fn;

    auto result = std::invoke(fn, 1, "2");
    std::cout << result << std::endl;
    auto cast_bool = static_cast<bool>(result);
    std::cout << std::boolalpha << cast_bool << std::endl;

    std::cout << std::is_same<char, std::invoke_result_t<Fn, int, int>>::value;
    
    return 0;
}
