#include <QtCore/QCoreApplication>
#include "GuiWidget.h"

class obj
{
public:
    
    int foo(int a, int b)
    {
        return a + b;
    }
};

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    //
    // GuiWidget w;
    // w.show();

    static int b;
    int c;
    int* bd = &b;
    auto cd = &c;
    int* d = new int{0};

    obj o;
    *d = o.foo(b, c);
    *d = o.foo(1, 2);
    

    delete bd;
    delete bd;

    //return a.exec();
    return 0;
}
