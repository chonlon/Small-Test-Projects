#include "fiber.h"
#include "sylar.h"

auto g_logger = SYLAR_LOG_ROOT();

void run_in_fiber() {
    SYLAR_LOG_INFO(g_logger) << "run_in_fiber begin";

    sylar::Fiber::GetThis()->YieldHold();

    SYLAR_LOG_INFO(g_logger) << "run_in_fiber end";
    sylar::Fiber::GetThis()->YieldHold();
}

int main() {
    sylar::Fiber::GetThis();
    SYLAR_LOG_INFO(g_logger) << "main begin";
    sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));

    fiber->swapIn();
    SYLAR_LOG_INFO(g_logger) << "main after swapIn";
    fiber->swapIn();
    SYLAR_LOG_INFO(g_logger) << "main at end";

    return 0;
}

