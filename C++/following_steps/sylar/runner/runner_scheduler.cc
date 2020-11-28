#include "sylar.h"

auto g_logger = SYLAR_LOG_ROOT();

void test_fiber() {
    SYLAR_LOG_INFO(g_logger) << "test in fiber";
    static int count = 10;
    sleep(1);
    if(--count >= 0) {
        sylar::Scheduler::GetThis()->schedule(&test_fiber, sylar::GetThreadId());
    }
}

int main() {
    SYLAR_LOG_INFO(g_logger) << "begin";
    sylar::Scheduler sc{3, false, "test"};
    sc.start();
    sc.schedule(&test_fiber);
    sc.stop();
    SYLAR_LOG_INFO(g_logger) << "over";
    return 0;
}