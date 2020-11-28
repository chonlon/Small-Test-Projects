#include "Config.h"
#include <test.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#ifdef USE_MYMATH
#  include "MathFunctions.h"
#endif

int main(int argc, char* argv[])
{
    if (argc < 2) {
        // report version
        std::cout << argv[0] << " Version " << Test_VERSION_MAJOR << "."
            << Test_VERSION_MINOR << std::endl;
        return 1;
    }
    // convert input to double
    const double inputValue = atof(argv[1]);

    // calculate square root
#ifdef USE_MYMATH
    const double outputValue = mysqrt(inputValue);
#else
    const double outputValue = sqrt(inputValue);
#endif
    std::cout << "The square root of " << inputValue << " is " << outputValue
        << std::endl;
    std::cout << foo()  << "----"<< '\n';
    return 0;
}