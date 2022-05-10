#pragma once
#include <QThread>
#include <QMap>
#include <QDebug>

//using type = std::pair<QString, QString>;
struct type{
    QString first;
    QString second;
};

struct type2 {
    type2() {  }
    type2(const type2& type2_) {
        qDebug() << "cctor";
    }

    QString s{"12312312"};
};

Q_DECLARE_METATYPE(type)
Q_DECLARE_METATYPE(type2)


class Sender : public QThread {
Q_OBJECT
public:


void run() override {
    {
        type2 t;
         emit sig2(t);
        qDebug() << QThread::currentThread() ;
    }
    
    for(int i = 0;; ++i) {
        auto p =  new type{"1111111111", "2222222"};
        
        emit sig(*p);

        delete p;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}




Q_SIGNAL void sig(type t);
Q_SIGNAL void sig2(const type2& t);

};
