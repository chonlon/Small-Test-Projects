#include <vector>
#include <string>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/split.hpp>


int main()
{
    std::vector<std::string> texts{"hello\nwe all know we can do it\nyes", "world", "bill", "holly"};
    std::string text = texts | ranges::view::split('\n')
        | ranges::view::filter(std::vector<std::string>{"y"})|ranges::view::join("\n");
    return 0;
}