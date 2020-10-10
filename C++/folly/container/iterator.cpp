#include <folly/container/Iterator.h>

#include <vector>
#include <algorithm>

struct Widget { Widget(int, int){} };
std::vector<Widget> makeWidgets(const std::vector<int>& in) {
    std::vector<Widget> out;
    std::transform(
        in.begin(),
        in.end(),
        folly::back_emplacer(out),
        [](int i) { 
            return folly::make_emplace_args(i, i); 
        });
    return out;
}

int main() {
    makeWidgets({ 1, 2, 4, 5, 6 });
}