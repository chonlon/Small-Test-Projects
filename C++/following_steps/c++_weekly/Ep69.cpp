#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

int main() {
    std::string s{"search rather"};
    std::string sub{"rather"};

    std::vector<int> v{1,2,3};
    std::vector<int> v_sub{4, 3};

    auto found = std::search(s.begin(), s.end(), std::boyer_moore_searcher(sub.begin(), sub.end()));
    std::cout << *found << '\n';

    // find if和search的区别有点像any_of和all_of
    auto found_v_search = std::search(v.begin(), v.end(), v_sub.begin(), v_sub.end());
    auto found_v_any = std::find_first_of(v.begin(), v.end(), v_sub.begin(), v_sub.end());
    if(found_v_search == v.end()) std::cout << "search not found\n";
    if(found_v_any != v.end()) std::cout << "find first of get:" << std::distance(v.begin(), found_v_any) << '\n';
    
    return 0;
}