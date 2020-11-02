#include "log.h"

#include <iostream>

int main() {
    std::string s(sylar::LogLevel::toString(sylar::LogLevel::Level::INFO));
    std::cout << sylar::LogLevel::toString(sylar::LogLevel::Level::DEBUG);
}

