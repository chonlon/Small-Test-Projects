#include "sylar.h"

auto g_logger = SYLAR_LOG_ROOT();
int count = 0;
sylar::RWMutex rwlock;
void func1() {
    SYLAR_LOG_INFO(g_logger)
        << " name: " << sylar::Thread::GetName()
        << " this.name: " << sylar::Thread::GetThis()->getName()
        << " id: " << sylar::GetThreadId()
        << " this.id: " << sylar::Thread::GetThis()->getId();
    for(int i = 0; i < 1000000; ++i) {
        sylar::RWMutex::WriteLock locker(rwlock);
        ++count;
    }
}

void func2() {}

int main(int argc, char** argv) {
    SYLAR_LOG_INFO(g_logger) << "thread test begin";

    std::vector<sylar::Thread::ptr> thrs;
    for (int i = 0; i < 5; ++i) {
        sylar::Thread::ptr thr(
            new sylar::Thread(&func1, "name_" + std::to_string(i)));
        thrs.push_back(thr);
    }
    for (int i = 0; i < 5; ++i) {
        thrs[i]->join();
    }
    SYLAR_LOG_INFO(g_logger) << "thread test end";
    SYLAR_LOG_INFO(g_logger) << "count= " <<count;
    return 0;
}