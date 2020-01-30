#pragma once
#include <iostream>
///////////////////////////////////////////////
// functions
///////////////////////////////////////////////

void printDividing() {
    std::cout << "=======================================\n";
}

///////////////////////////////////////////////
// classes
///////////////////////////////////////////////

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

class IntField : public BaseField
{
    int var;

public:
    IntField(int _var) : var(_var)
    {
    }

    void print() { std::cout << "Int Field:" << var << "\n"; }
};