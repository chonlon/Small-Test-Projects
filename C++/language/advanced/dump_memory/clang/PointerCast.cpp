#include "TestClasses.hpp"
#include "../../../header/base.h"
#include <iostream>

unsigned long long calculateDistance(void* lhs, void* rhs) {
    return reinterpret_cast<unsigned long long>(lhs) - reinterpret_cast<unsigned long long>(rhs);
}

int main() {
    {
        CaseMarker c{ "SimpleInherit" };
        Base* b = new SimpleInherit();

        std::cout << calculateDistance(b, static_cast<SimpleInherit*>(b)) << '\n';
    }
    
    {
        CaseMarker c{ "MultiInherit" };
        
        Base* b0 = new MultiInherit();
        Base2* b = new MultiInherit();
        std::cout << calculateDistance(b0, static_cast<MultiInherit*>(b0)) << ' ' << calculateDistance(b, static_cast<MultiInherit*>(b)) << '\n';
    }
    
    {
        CaseMarker c{ "MultiInherit dynamic" };
        
        Base2* b = new MultiInherit();
        
        // 侧向转型（sidecast)
        std::cout << calculateDistance(b, dynamic_cast<Base*>(b)) << '\n';
    }
}