#include <folly/FBVector.h>
#include <vector>
#include <folly/FBString.h>
#include <iostream>

int main() {
    folly::fbvector<int> v{1, 2, 3};
    std::cout << v.capacity() << "\n";
    for(auto i = 4; i < 1000; ++i) {
        v.push_back(1);
        std::cout << v.capacity() << "\n";
    }
    std::cout << "<===================================>\n";
    std::vector<int> sv{1, 2, 3};
    for(auto i = 4; i < 1000; ++i) {
        sv.push_back(1);
        std::cout << sv.capacity() << "\n";
    }
    std::cout << std::endl;
    

    return 0;
}
