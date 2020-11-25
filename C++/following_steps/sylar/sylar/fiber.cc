#include "fiber.h"
#include "config.h"
#include "macro.h"

#include <atomic>


namespace sylar {
static std::atomic<uint64_t> s_fiber_id{0};
static std::atomic<uint64_t> s_fiber_count{0};
static thread_local Fiber* t_fiber = nullptr;
static thread_local std::shared_ptr<Fiber> t_threadFiber = nullptr;

static ConfigVar<uint32_t>::ptr g_fiber_stack_size = Config::lookUp<uint32_t>("fiber.stack_size", 1024*1024, "fiber stack size");


class MallocStackAllocator
{
public:
    static void* Alloc(size_t size) {
        return malloc(size);
    }

    static void Dealloc(void* vp, size_t size) {
        return free(vp);
    }
};

using StackAllocator = MallocStackAllocator;

Fiber::Fiber() {
    m_state = State::EXEC;
    SetThis(this);
    if (getcontext(&m_ucontext)) {
        SYLAR_ASSERT2(false, "getcontext");
    }
    ++s_fiber_count;
}

Fiber::Fiber(std::function<void()> cb, size_t stack_size) : m_id{++s_fiber_id},
m_cb{cb}
{
    ++s_fiber_count;
    m_stackSize = stack_size ? stack_size : g_fiber_stack_size->getValue();

    m_stack = StackAllocator::Alloc(m_stackSize);
    if(getcontext(&m_ucontext)) {
        SYLAR_ASSERT2(false, "setcontext");
    }
    m_ucontext.uc_link = nullptr;
    m_ucontext.uc_stack.ss_sp = m_stack;
    m_ucontext.uc_stack.ss_size = m_stackSize;
    makecontext(&m_ucontext, &Fiber::MainFunc, 0);
}

Fiber::~Fiber() {
    --s_fiber_count;
    if(m_stack) {
        SYLAR_ASSERT(m_state == State::TERM || m_state == State::INIT);
        StackAllocator::Dealloc(m_stack, m_stackSize);
    } else {

        // 主协程
        SYLAR_ASSERT(!m_cb);
        SYLAR_ASSERT(m_state == State::EXEC);

        Fiber* cur = t_fiber;
        if(cur == this) {
            SetThis(nullptr);
        }
    }
}

void Fiber::reset(std::function<void()> cb) {
}

void Fiber::swapIn() {
}

void Fiber::swapOut() {
}

void Fiber::SetThis(Fiber* fiber) {
}

Fiber::ptr Fiber::GetThis() {
}

void Fiber::YieldReady() {
}

void Fiber::YieldHold() {
}

uint64_t Fiber::TotalFibers() {
}

void Fiber::MainFunc() {
}


}
