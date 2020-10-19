#include <folly/Range.h>

#include <boost/algorithm/string/trim.hpp>
#include <boost/range/concepts.hpp>

#include "../Tests/cache2/catch.hpp"

#include <iostream>
#include <string>


using namespace folly;
using namespace std;

static_assert(std::is_literal_type<StringPiece>::value, "");


int main() {
    const char* foo = "foo";
    const char* foo2 = "foo";

    string fooStr(foo);
    string foo2Str(foo2);
}