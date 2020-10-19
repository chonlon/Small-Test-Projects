#include <iostream>
#include "../../header/base.h"

// 测试class里面成员变量初始化采用的方式



class Object{
    int var = 10;

    IntField int_field_ = 10;
public:
    Object() = default;
    // 可以看出来这里的优先级是高于上面的 var =10 的优先级的
    // 并且并没有执行两次初始化IntField.
    Object(int _var) : var(_var), int_field_(_var) {}

    void print() {
        std::cout << "var value: " << var << std::endl;
        int_field_.print();
    }
};

int main() {
    printDividing();
    Object{}.print();
    printDividing();
    Object{5}.print();
}