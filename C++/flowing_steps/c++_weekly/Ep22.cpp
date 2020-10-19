#include "../../header/base.h"

#include <algorithm>

namespace org::group::project::internal {
    struct MyStruct {};
}

int main(int argc, char** argv) {
    {
        // nested namespace build success.
        org::group::project::internal::MyStruct s;
    }
    
    {
        CaseMarker c{ "clamp" };
        std::cout << (argc < 2 ? 2 : ((argc > 5) ? 5 : argc)) << '\n';
        // same with boost clamp.
        std::cout << std::clamp(argc, 2, 5) << '\n';
    }
}