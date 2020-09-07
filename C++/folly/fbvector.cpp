#include <folly/FBVector.h>
#include <vector>
#include <folly/FBString.h>
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

// not using std alloctor will not use memcpy to move and will destory old memory manually.

int main() {
    folly::fbvector<int> v{1, 2, 3};
    
    int _capacity = v.capacity();
    int same_marker = 0;
    std::cout << _capacity << "\n";
    for(auto i = 4; i < 10000; ++i) {
        v.push_back(1);
        _capacity =  v.capacity();
        if(_capacity != same_marker) {
            std::cout << _capacity << "\n";
            same_marker = _capacity;
        }
    }
    folly::fbvector<folly::fbstring> strings{"1", "1", "1"};
    for(auto i = 4; i < 10000; ++i) {
        strings.push_back("1");
    }
    std::cout << "<===================================>\n";
    std::vector<int> sv{1, 2, 3};
    for(auto i = 4; i < 1000; ++i) {
        sv.push_back(1);
        _capacity = sv.capacity();
        if(_capacity != same_marker) {
            std::cout << _capacity << "\n";
            same_marker = _capacity;
        }
    }
    std::cout << std::endl;


    std::cout << "<===================================>\n";
    folly::fbvector<int, myalloctor<int>> mfv{1, 2, 3};
    for(auto i = 4; i < 10; ++i) {
        mfv.push_back(1);
    }
    for(auto& i : mfv) {
        std::cout << i << ' ';
    }
    return 0;
}
