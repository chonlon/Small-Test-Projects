// 测试函数返回值生存时间.
#include <iostream>

#include <string>

class Object
{
public:
    Object()
    {
        static int ii = 0;
        i  = ++ii;
        std::cout  << "ctor "<< i << "\n";
    }

    Object(const Object& obj)
    {
        static int ii = 0;
        i = --ii;
        std::cout << "cp ctor" << i << "\n";
    }

    int* getData()
    {
        return &i;
    }

    ~Object()
    {
        std::cout << "dtor " << i << "\n";
    }

private:
    int i;
};

class Drived : public Object
{
public:
    Drived() : Object{} {}
    ~Drived() = default;
};


Object foo()
{
    return Object{};
}

void foo2(Object j)
{
    
}

int main()
{
    std::cout << "1<----------------------->\n";
    foo();

    std::cout << "2<----------------------->\n";
    auto i = foo();

    std::cout << "2.1<----------------------->\n";
    auto ii = foo().getData();
    std::cout << *ii << "value test \n";

    std::cout << "3<----------------------->\n";
    foo2(i);

    std::cout << "4<----------------------->\n";
}
