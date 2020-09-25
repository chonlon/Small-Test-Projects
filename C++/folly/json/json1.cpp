#include <folly/json.h>
#include <iostream>
#include "../../header/base.h"

using namespace std;
using folly::dynamic;

int main() {
    // clang-format off
    dynamic value = dynamic::object
        ("foo", "bar")
        ("junk", 12)
        ("another", 32.2)
        ("a",
        dynamic::array(
            dynamic::object("a", "b")("c", "d"),
            12.5,
            "Yo Dawg",
            dynamic::array("heh"),
            nullptr));
    // clang-format on
    [&value](){
        folly::json::serialization_opts opt;
        opt.pretty_formatting = false;
        opt.sort_keys = true;
        cout << folly::json::serialize(value, opt) << "\n";
        printDividing("1");

        opt.sort_keys = false;
        cout << folly::json::serialize(value, opt) << "\n";

        printDividing("2");

        auto s = folly::toJson(value);

        cout << s  << "\n";
        printDividing("3");


        cout << folly::toPrettyJson(value) << "\n";
    }();
    

    printDividing("4");
    cout << "\n\n";
    printDividing("5");

    auto s = std::string{
        "{"
        "\"junk\": 12,"
        "\"foo\": \"bar\","
        "\"a\": ["
            "{"
            "\"a\": \"b\","
            "\"c\": \"d\""
            "},"
            "12.5,"
            "\"Yo Dawg\","
            "["
            "\"heh\""
            "],"
            "null"
        "],"
        "\"another\": 32.2"
        "}"
    };
    folly::json::serialization_opts opt;
        opt.pretty_formatting = true;
        opt.sort_keys = false;
    auto dynamic = folly::parseJson(s, opt);
    dynamic["junk"] = 15;
    auto result = folly::json::serialize(dynamic, opt);
    cout << sizeof(decltype(dynamic));
    cout << result;
}
