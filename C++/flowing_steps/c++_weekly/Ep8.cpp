#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

//g++ Ep8.cpp
//nm . / a.out | c++filt - t
//. / a.out

struct MyClass
{
    std::vector<std::vector<std::list<std::pair<std::string, std::string>>>> data_;
};

 int main() {
     MyClass s;
     
     int status;
     std::cout << abi::__cxa_demangle(typeid(&MyClass::data_).name(), nullptr, 0, &status) << '\n';
 }