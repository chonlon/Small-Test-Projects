#pragma once
#include <QTime>

class TimeSpanCollector {

    TimeSpanCollector(int* result)
        : result_(result) {
        span_.start();
    }

    ~TimeSpanCollector() {
        *result_ = span_.elapsed();
    }

private:
    int*  result_;
    QTime span_;
};