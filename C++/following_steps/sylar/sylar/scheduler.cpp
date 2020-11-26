#include "scheduler.h"
#include "log.h"

namespace sylar {

static auto g_logger = SYLAR_LOG_NAME("system");


Scheduler::~Scheduler() {
    
}

static Scheduler* Scheduler::GetThis() {
    
}

static Fiber* Scheduler::GetMainFiber() {
    
}

void Scheduler::start() {
    
}

void Scheduler::stop() {
    
}

MutexType::Locker Scheduler::locker(m_mutex) {
    
}

void Scheduler::tickle() override {
    
}

FiberAndThread Scheduler::ft(fc, thread) {
    
}

}