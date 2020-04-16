#include "QChildWasDeleteAlready.h"

class W : public QWidget
{
public:
    explicit W(QWidget* p) : QWidget(p)
    {  }

    char i[100000000];
};

QChildWasDeleteAlready::QChildWasDeleteAlready(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    for(auto i = 0; i < 10; ++i) {
        auto w = new W{this};
        delete w;
    }
}
