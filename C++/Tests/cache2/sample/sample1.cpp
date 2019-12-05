#define CATCH_CONFIG_MAIN

#include "../catch.hpp"

int add(int a, int b) {
    return a + b;
}

TEST_CASE("Test Add Function") {
    REQUIRE(add(1, 2) == 3);
    REQUIRE(add(3, 4) == 7);
    REQUIRE(add(1, 1) == 2);
}