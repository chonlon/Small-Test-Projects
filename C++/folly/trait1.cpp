#include <folly/Traits.h>
#include <iostream>

class RelocateFalseType{
private:
    typedef std::false_type IsRelocatable;
};

class RelocateTrueType{
public:
    typedef std::true_type IsRelocatable;
};

class RelocateTrueType1 {
public:
    typedef std::false_type IsRelocatable;
};

int main() {
    std::cout << std::boolalpha << "true type:" <<folly::traits_detail::has_IsRelocatable<RelocateTrueType>::value << "\n"
    << "true type:" <<folly::traits_detail::has_IsRelocatable<RelocateTrueType1>::value << "\n"
    << "false type:" <<folly::traits_detail::has_IsRelocatable<RelocateFalseType>::value << "\n";
}
