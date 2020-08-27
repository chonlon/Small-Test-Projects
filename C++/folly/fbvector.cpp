#include <folly/FBVector.h>
#include <vector>
#include <folly/FBString.h>
#include <iostream>

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
    std::cout << std::endl;

    return 0;
}
