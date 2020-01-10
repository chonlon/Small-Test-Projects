#define CATCH_CONFIG_MAIN

#include "globalvar1.h"
#include "Tests/cache2/catch.hpp"


const char* pp = "hello";
static char* ppp = "hello";

TEST_CASE("test global var") {
    // 这里的两个指针p和pp会被优化为指向同一个地方的指针.
    REQUIRE(p == pp);

    REQUIRE_FALSE(pp == ppp);
}