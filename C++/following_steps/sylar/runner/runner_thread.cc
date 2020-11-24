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

void func2() {
    while(true)
        SYLAR_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    
}

void func3() {
    while(true)
        SYLAR_LOG_INFO(g_logger) << "====================================================";
}

int main(int argc, char** argv) {
    SYLAR_LOG_INFO(g_logger) << "thread test begin";
    YAML::Node root = YAML::LoadFile("log2.yml");
    sylar::Config::LoadFromYaml(root);
    constexpr int thread_num = 2;

    std::vector<sylar::Thread::ptr> thrs;
    for (int i = 0; i < thread_num; ++i) {
        sylar::Thread::ptr thr(
            new sylar::Thread(&func2, "name_" + std::to_string(i)));
        sylar::Thread::ptr thr2(
            new sylar::Thread(&func3, "name_" + std::to_string(i)));
        thrs.push_back(std::move(thr));
        thrs.push_back(std::move(thr2));
    }
    for (int i = 0; i < thread_num; ++i) {
        thrs[i]->join();
    }
    SYLAR_LOG_INFO(g_logger) << "thread test end";
    SYLAR_LOG_INFO(g_logger) << "count= " <<count;
    return 0;
}