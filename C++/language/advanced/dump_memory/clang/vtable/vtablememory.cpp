#include "../TestClasses.hpp"
#include "../../SimpleDumpBinary.hpp"

int main() {
    SimpleInherit s;
    
    auto vp = reinterpret_cast<void**>(&s);
    
    dumpobject(&s);
    
    return 0;
}