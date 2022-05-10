#include <QtCore/QCoreApplication>
#include <iostream>
#include <thread>

void f(char * ppp)
{
    std::cout << std::hex << reinterpret_cast<long long>(ppp) << "\n";
}

class T
{
public:
    char* p;

    char* data()
    {
        return p;
    }

    T()
    {
        p = new char[10]{'a'};
    }

    T(const T& t)
    {
        p = t.p;
        std::cout << "cctor";
    }

    T(T&& t)
    {
        p = t.p;
        std::cout << "mctor";
        t.p = nullptr;
    }
    
    ~T()
    {
        //delete p;
        std::cout << "dtor\n";
    }
};

class CT
{
public:
    T createT()
    {
        return T{};
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char* p;
    QByteArray arr;
    {
        char str1[10]{0};
        for(auto i = 0; i < 9; ++i) {
            str1[i] = 'h';
        }
        std::cout<< std::hex << reinterpret_cast<long long>(str1) << "\n";
        p = str1;
        {
            
        }
        arr.append(str1);
    }


    auto arrp = arr.data();
    // exec deep copy.
    std::cout << std::hex << reinterpret_cast<long long>(arrp) << "\n";

    {
        QString s{"123123123"};auto d = s.toUtf8();
        auto newd = new QByteArray{d};
        {
            auto b = s.toUtf8();
            p = newd->data();
            std::cout << std::hex << reinterpret_cast<long long>(d.data()) << "\n";
            std::cout << std::hex << reinterpret_cast<long long>(b.constData()) << "\n";
        }
        {
            f(newd->data());
            f(s.toUtf8().data());
            delete newd;
            f(p);
        }
        std::cout << std::hex << reinterpret_cast<long long>(s.toUtf8().data()) << "\n";
        
    }

    std::cout << "-------------\n";
    {
        CT ct;
        f(ct.createT().data());
        auto t = ct.createT();
        f(t.data());
    }
    

    

    return a.exec();
}
