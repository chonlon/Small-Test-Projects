#include <memory>
#include "../../header/base.h"
//#include <gtest/gtest.h>

std::shared_ptr<int> sfoo() {
    auto p = std::make_shared<int>(1);
    return p;
}

std::unique_ptr<BaseField> ufoo() {
    auto p = std::make_unique<BaseField>();
    return p;
}

void foos(std::shared_ptr<int> sp) {
    std::cout << "<==>" << " " << *sp << " "<< __FUNCTION__ << "\n";
}

void foou(std::unique_ptr<BaseField> up) {
    std::cout << "<==> " << " " << __FUNCTION__ << "\n"; 
}

int main() {
    printDividing();
    auto sp = sfoo();
    foos(sp);
    printDividing();
    auto up = ufoo();
    foou(std::move(up));
    printDividing();
}