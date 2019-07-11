#include "window.h"
#include <QApplication>
#include <QStandardItemModel>
#include <QStringList>
#include <QList>
#include <QMap>

#include <QDebug>

QAbstractItemModel* createModel() {
    QList<QStandardItem*> item_list;

    auto model = new QStandardItemModel{};
    model->setHorizontalHeaderLabels(QStringList{"one", "two", "three"});

    for(auto i = 0; i < 10; ++i) {
        QList<QStandardItem*> item_list;
        for(auto j = 0; j < 3; ++j) {
            item_list << new QStandardItem{QString::number(i*3 + j)};
        }
        model->appendRow(item_list);
    }

    return model;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.setSourceModel(createModel());
    w.show();

    return a.exec();
}

//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    QPushButton button("Quit");
//    QObject::connect(&button, &QPushButton::clicked, [](bool) {
//        qDebug() << "You clicked me!";
//    });
//    button.show();

//    return app.exec();
//}
