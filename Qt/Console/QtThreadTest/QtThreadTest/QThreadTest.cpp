#include "QThreadTest.h"
#include <QDebug>
#include <chrono>


QThreadTest::QThreadTest() {

}


QThreadTest::~QThreadTest() {
}

void QThreadTest::foo() {
    mutex_.lock();

    for (auto i = 0; i < 10000000; ++i) {
        int a = 0;
    }

    mutex_.unlock();
}

void QThreadTest::run() {
    mutex_.lock();
    for (auto i = 0; i < 10000000; ++i) {
        int a = 0;
    }
    mutex_.unlock();
}

void QThreadTest::timerEvent(QTimerEvent* event) {
    static int i = 0;
    qDebug() << "timer thread" << QThread::
        currentThread();
    qDebug() << "we are now at " << i;
}
