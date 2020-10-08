#include <vector>
#include <algorithm>
#include "../header/base.h"

std::vector<int> make_vec() {
    return  { 1, 2, 3, 4};
}

int main() {
    auto vec = make_vec();
    
    if (const auto itr = std::find(vec.begin(), vec.end(), 2); itr != vec.end()) {
        *itr = 3;
    }
    
    lon::printContainer(vec, ' ');
    
    if (const auto itr = std::find(vec.begin(), vec.end(), 3);itr != vec.end()) {
        *itr = 4;
    } else {
        // itr aviable in this scope.
        vec.insert(itr, 6);
    }
    
    lon::printContainer(vec, ' ');
}
