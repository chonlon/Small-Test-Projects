#include <QtCore/QCoreApplication>
#include <QDebug>
#include "Sender.h"


// connect queuedconection �ڲ�ͬ�̵߳������signal��������const ���û�ʹ�ø��ƹ�������װ��ȫ, 

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
