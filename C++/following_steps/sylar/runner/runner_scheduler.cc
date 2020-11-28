#include "sylar.h"

auto g_logger = SYLAR_LOG_ROOT();

void test_fiber() {
    SYLAR_LOG_INFO(g_logger) << "test in fiber";
}

int main() {
    SYLAR_LOG_INFO(g_logger) << "begin";
    sylar::Scheduler sc{};
    sc.schedule(&test_fiber);
    sc.start();

    sc.stop();
    SYLAR_LOG_INFO(g_logger) << "over";
    return 0;
}