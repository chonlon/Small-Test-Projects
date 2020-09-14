#include <list>
#include <map>
#include <vector>
#include <iostream>

#include <boost/assign/std/vector.hpp>
#include <boost/assign/std/list.hpp>
#include <boost/assign/std/map.hpp>
#include <boost/assign.hpp>

#include "../../../header/base.h"

using namespace std::string_literals;
using namespace std;
using namespace lon::print_container;
using namespace boost::assign;


int main() {
    {
        CaseMarker c("vector");
        vector<int> v {1, 2, 3};
        v += 4, 5, 6, 7, 8, 9, 10;
        push_back(v)(11)(12)(13);
        lon::printContainer(v, ' ');
        cout << '\n';
    }
    {
        CaseMarker c("list");
        list<int> l{2, 3, 4};
        l += 5, 6, 7, 8;
        push_front(l)(0)(-1);
        push_back(l)(9)(10);
        lon::printList(l, ' ');
        cout << '\n';
    }
    {
        CaseMarker c("map");
        map<int, string> m{{1, "hello"},{2, "world"}};
        insert(m)(3, "!")(4, "!")(5, "!");
        lon::printMap(m);
    }

    return 0;
}
