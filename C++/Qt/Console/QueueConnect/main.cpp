#include <QtCore/QCoreApplication>
#include <QDebug>
#include "Sender.h"


// connect queuedconection 在不同线程的情况下signal参数采用const 引用会使用复制构造来包装安全, 

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Sender s;
    s.start();
    QObject::connect(&s, &Sender::sig, &s, [](type t)
    {
       qDebug() << t.first << t.second;
    }, Qt::QueuedConnection);

    QObject::connect(&s, &Sender::sig2, &s, [](const type2& t)
    {
       qDebug() << "------------type2 invoked-----------------" << t.s;
        qDebug() << QThread::currentThread() ;
    }, Qt::QueuedConnection);

    return a.exec();
}
