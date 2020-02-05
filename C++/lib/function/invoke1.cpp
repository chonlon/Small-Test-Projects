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
    std::cout << std::invoke(fn, 1, "a") << std::endl;
    return 0;
}
