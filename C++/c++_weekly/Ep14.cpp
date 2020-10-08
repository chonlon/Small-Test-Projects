#include "../header/base.h"

#include <vector>
#include <algorithm>
#include <iostream>

#include <list>

int main() {
    printDividing(" std::next ");
    std::list<int> v{ 1, 2, 3, 4, 5, 6, 7 };
    std::cout << std::is_sorted(std::next(std::begin(v)), std::end(v)) << '\n';
    printDividing(" std::exchange ");
    auto old_value = std::exchange(*v.begin(), 0);
    std::cout << "old value: " << old_value << '\n';
    lon::printContainer(v, ' ');
}