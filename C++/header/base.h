#pragma once
#include <iostream>
#include <string>
///////////////////////////////////////////////
// micros
///////////////////////////////////////////////

#define PRINT_INVOKED() \
    std::cout << "was invoked: " << __FUNCTION__;

///////////////////////////////////////////////
// functions
///////////////////////////////////////////////

void printDividing() {
    std::cout << "=======================================\n";
}

void printDividing(std::string&& s) {
    std::cout << "===================" << s << "====================\n";
}


///////////////////////////////////////////////
// classes
///////////////////////////////////////////////

/// <summary> base field that count all this class construct time, and print when construct and destruct </summary>
class BaseField
{
    int construct_time_;

public:
    BaseField()
    {
        static int construct_time = 0;
        construct_time_ = ++construct_time;
        std::cout << "BaseField Ctor"
                  << "--" << construct_time_ << "\n";
    }
    ~BaseField()
    {
        std::cout << "BaseField Dtor"
                  << "--" << construct_time_ << "\n";
    }
};

/// <summary> an intfield that prints int</summary>
class IntField : public BaseField
{
    int var_;

public:
    IntField(int _var) : var_(_var)
    {
    }

    void print() { std::cout << "Int Field:" << var_ << "\n"; }
};