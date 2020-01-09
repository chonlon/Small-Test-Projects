#include <folly/FBVector.h>
#include <folly/FBString.h>
#include <jemalloc/jemalloc.h>
#include <iostream> 

int main()
{
    if (mallocx == nullptr)
    {
    }
    if (rallocx == nullptr)
    {
        int a = 0;
    }
    if (xallocx == nullptr)
    {
        int a = 0;
    }
    if (sallocx == nullptr)
    {
        int a = 0;
    }
    if (dallocx == nullptr)
    {
        int a = 0;
    }
    if (sdallocx == nullptr)
    {
        int a = 0;
    }
    if (nallocx == nullptr)
    {
        int a = 0;
    }
    if (mallctl == nullptr)
    {
        int a = 0;
    }
    if (mallctlnametomib == nullptr)
    {
        int a = 0;
    }
    if (mallctlbymib == nullptr)
    {
        int a = 0;
    }

    folly::fbvector<int> v{1, 2, 3};

    v.push_back(4);
    v.push_back(5);

    for(auto i = 0; i < 10000; ++i) {
        v.push_back(i);
    }

    std::cout << v[0];

    folly::fbvector<folly::fbstring> strings{"hello", "world", "!"};

    strings.push_back("From China!");
    strings.push_back("last");

    for(auto i = 0; i < 10000; ++i) {
        strings.push_back("1");
    }
}