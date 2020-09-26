#include <folly/Format.h>
#include <iostream>

int main() {
    using folly::format;
    using folly::sformat;
    using folly::svformat;
    using folly::vformat;

    // Objects produced by format() can be
    // streamed without creating an intermediary
    // string; {} yields the next argument using
    // default formatting.
    std::cout << format(
                     "The answers are {} and {}",
                     23,
                     42)
              << "\n";
    // => "The answers are 23 and 42"

    // If you just want the string, though, you're
    // covered.
    std::string result = sformat(
        "The answers are {} and {}", 23, 42);
    // => "The answers are 23 and 42"
    std::cout << result << "\n";

    // To insert a literal '{' or '}', just double
    // it.
    std::cout << format("{} {{}} {{{}}}", 23, 42)
              << "\n";
    // => "23 {} {42}"

    // Arguments can be referenced out of order,
    // even multiple times
    std::cout << format(
                     "The answers are {1}, {0}, "
                     "and {1} again",
                     23,
                     42)
              << "\n";
    // => "The answers are 42, 23, and 42 again"

    // It's perfectly fine to not reference all
    // arguments
    std::cout << format("The only answer is {1}",
                        23,
                        42)
              << "\n";
    // => "The only answer is 42"

    std::cout << "======================2========"
                 "=======\n";

    // Values can be extracted from indexable
    // containers (random-access sequences and
    // integral-keyed maps), and also from
    // string-keyed maps
    std::vector<int>                   v{23, 42};
    std::map<std::string, std::string> m{
        {"what", "answer"}};
    std::cout
        << format("The only {1[what]} is {0[1]}",
                  v,
                  m)
        << "\n";
    // => "The only answer is 42"

    std::cout << "======================3========"
                 "=======\n";

    // If you only have one container argument,
    // vformat makes the syntax simpler
    std::map<std::string, std::string> m2{
        {"what", "answer"}, {"value", "42"}};
    std::cout << vformat(
                     "The only {what} is {value}",
                     m2)
              << "\n";
    // => "The only answer is 42"
    // same as
    std::cout
        << format(
               "The only {0[what]} is {0[value]}",
               m2)
        << "\n";
    // => "The only answer is 42"
    // And if you just want the string,
    std::string result2 = svformat(
        "The only {what} is {value}", m2);
    // => "The only answer is 42"
    std::string result3 = sformat(
        "The only {0[what]} is {0[value]}", m2);
    // => "The only answer is 42"

    std::cout << result2 << "\n"
              << result3 << "\n";

    std::cout << "======================4========"
                 "=======\n";

    // {} works for vformat too
    std::vector<int> v2{42, 23};
    std::cout << vformat("{} {}", v2) << "\n";
    // => "42 23"

    // format and vformat work with pairs and
    // tuples
    std::tuple<int, std::string, int> t{
        42, "hello", 23};
    std::cout << vformat("{0} {2} {1}", t) << "\n";
    // => "42 23 hello"

    // Format supports width, alignment, arbitrary
    // fill, and various format specifiers, with
    // meanings similar to printf "X<10": fill
    // with 'X', left-align ('<'), width 10
    std::cout << format(
        "{:X<10} {}", "hello", "world") << "\n";
    // => "helloXXXXX world"


    std:: cout << "======================5===============\n";


    // Field width may be a runtime value rather
    // than part of the format string
    int x = 6;
    std::cout << format("{:-^*}", x, "hi") << "\n";
    // => "--hi--"

    // Explicit arguments work with dynamic field
    // width, as long as indexes are given for
    // both the value and the field width.
    std::cout << format("{2:+^*0}",
                        9,
                        "unused",
                        456) << "\n";  // => "+++456+++"

    // Format supports printf-style format
    // specifiers
    std::cout << format(
        "{0:05d} decimal = {0:04x} hex", 42) << "\n";
    // => "00042 decimal = 002a hex"

    // Formatter objects may be written to a
    // string using folly::to or folly::toAppend
    // (see folly/Conv.h), or by calling their
    // appendTo(), str(), and fbstr() methods
    std::string s =
        format("The only answer is {}", 42).str();
    std::cout << s << "\n";
    // => "The only answer is 42"

    // Decimal precision usage
    std::cout << format(
        "Only 2 decimals is {:.2f}",
        23.34134534535) << "\n";
}