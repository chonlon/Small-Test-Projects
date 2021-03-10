#include "../base.h"

#include <set>
#include <vector>


int main() {
    {
        CaseMarker c{"vector set test"};
        std::vector<std::set<int>> vecs{{1, 2, 3}, {2, 3, 4}, {4, 5, 6}};
        lon::printContainer(vecs, '|');
        std::cout << '\n';
    }

    {
        CaseMarker c{"map test"};
        std::map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
        lon::printContainer(map);
    }

    {
        CaseMarker c{"vector vector vector test"};
        std::vector<std::vector<std::vector<int>>> vecs{
            {{1, 2, 3}, {2, 3, 4}, {4, 5, 6}},
            {{10, 20, 30}, {40, 50}},
            {{100, 200, 300}}};
        // std::vector<int> vecs{1, 2, 3};
        lon::doPrintContainer(vecs);
    }


    {
        CaseMarker c{"vector map test"};
        std::vector<std::map<std::string, int>> _map{{{"123", 1}, {"1cc", 2}},
                                                     {{"gg", 10}, {"hp", 111}}};
        lon::doPrint(_map);
        std::cout << '\n';
        
        
    }


    return 0;
}
