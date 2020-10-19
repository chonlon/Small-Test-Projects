#include <folly/FBVector.h>
#include <iostream>

template <typename T>
class myalloctor : public std::allocator<T>
{
private:
    using Allocator = std::allocator<T>;
    int unused;
public:
    myalloctor() : Allocator() {}
    /* implicit */ myalloctor(const Allocator& alloc)
        : Allocator(alloc) {}
    /* implicit */ myalloctor(Allocator&& alloc)
        : Allocator(std::move(alloc)) {}
    myalloctor(size_t n, const Allocator& alloc)
    : Allocator(alloc) {}
};


int main() {
    folly::fbvector<int, myalloctor<int>> mfv{1, 2, 3};
    for(auto i = 4; i < 10; ++i) {
        mfv.push_back(1);
    }
    for(auto& i : mfv) {
        std::cout << i << ' ';
    }
    return 0;
}