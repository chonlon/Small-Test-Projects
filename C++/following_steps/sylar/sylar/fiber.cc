#include "fiber.h"
#include "config.h"
#include "macro.h"
#include "scheduler.h"
#include "util.h"
#include <atomic>

static auto g_logger = SYLAR_LOG_NAME("system");

namespace sylar {
static std::atomic<uint64_t> s_fiber_id{0};
static std::atomic<uint64_t> s_fiber_count{0};
static thread_local Fiber* t_fiber                       = nullptr;
static thread_local std::shared_ptr<Fiber> t_threadFiber = nullptr;

static ConfigVar<uint32_t>::ptr g_fiber_stack_size = Config::lookUp<uint32_t>(
    "fiber.stack_size", 1024 * 1024, "fiber stack size");


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
    SYLAR_LOG_INFO(g_logger) << "Fiber Ctor";
    m_state = State::EXEC;
    SetThis(this);
    if (getcontext(&m_ucontext)) {
        SYLAR_ASSERT2(false, "getcontext");
    }
    ++s_fiber_count;
}

void Fiber::doInitFiber(size_t stack_size) {
    SYLAR_LOG_INFO(g_logger) << "Fiber Ctor"
                             << " id :" << m_id;
    ++s_fiber_count;
    m_stackSize = stack_size ? stack_size : g_fiber_stack_size->getValue();

    m_stack = StackAllocator::Alloc(m_stackSize);
    if (getcontext(&m_ucontext)) {
        SYLAR_ASSERT2(false, "setcontext");
    }

    // init m_ucontext
    m_ucontext.uc_link          = nullptr;
    m_ucontext.uc_stack.ss_sp   = m_stack;
    m_ucontext.uc_stack.ss_size = m_stackSize;
}

Fiber::Fiber(std::function<void()> cb, size_t stack_size)
    : m_id{++s_fiber_id}, m_cb{cb} {
    doInitFiber(stack_size);
    makecontext(&m_ucontext, &Fiber::MainFunc, 0);
}

Fiber::Fiber(std::function<void()> cb, size_t stack_size, bool use_caller)
    : m_id{++s_fiber_id}, m_cb{cb} {
    doInitFiber(stack_size);
    makecontext(&m_ucontext, &Fiber::CallerMainFunc, 0);
}

Fiber::~Fiber() {
    SYLAR_LOG_INFO(g_logger) << "Fiber Dtor"
                             << " id :" << m_id;
    --s_fiber_count;
    if (m_stack) {
        SYLAR_ASSERT(m_state == State::TERM || m_state == State::INIT ||
                     m_state == State::EXCEPT);
        StackAllocator::Dealloc(m_stack, m_stackSize);
    } else {

        // 主协程
        SYLAR_ASSERT(!m_cb);
        SYLAR_ASSERT(m_state == State::EXEC);

        Fiber* cur = t_fiber;
        if (cur == this) {
            SetThis(nullptr);
        }
    }
}

void Fiber::reset(std::function<void()> cb) {
    SYLAR_ASSERT(m_stack);
    SYLAR_ASSERT(m_state == State::TERM || m_state == State::INIT ||
                 m_state == State::EXCEPT);
    m_cb = cb;
    if (getcontext(&m_ucontext)) {
        SYLAR_ASSERT2(false, "getcontext");
    }

    m_ucontext.uc_link          = nullptr;
    m_ucontext.uc_stack.ss_sp   = m_stack;
    m_ucontext.uc_stack.ss_size = m_stackSize;
    makecontext(&m_ucontext, &Fiber::MainFunc, 0);
    m_state = State::INIT;
}

void Fiber::call() {
    SetThis(this);
    m_state = State::EXEC;
    SYLAR_LOG_INFO(g_logger) << getId();
    if (swapcontext(&t_threadFiber->m_ucontext, &m_ucontext)) {
        SYLAR_ASSERT2(false, "swapcontext");
    }
}

void Fiber::back() {
    SetThis(t_threadFiber.get());
    if (swapcontext(&m_ucontext, &(t_threadFiber->m_ucontext))) {
        SYLAR_ASSERT2(false, "swapcontext");
    }
}
void Fiber::swapIn() {
    SetThis(this);
    SYLAR_ASSERT(m_state != State::EXEC);
    m_state = State::EXEC;
    if (swapcontext(&(Scheduler::GetMainFiber()->m_ucontext), &m_ucontext)) {
        SYLAR_ASSERT2(false, "swapcontext");
    }
}

void Fiber::swapOut() {
    // SetThis(Scheduler::GetMainFiber());
    SetThis(Scheduler::GetMainFiber());
    if (swapcontext(&m_ucontext, &(Scheduler::GetMainFiber()->m_ucontext))) {
        SYLAR_ASSERT2(false, "swapcontext");
    }
}

void Fiber::SetThis(Fiber* fiber) {
    t_fiber = fiber;
}

Fiber::ptr Fiber::GetThis() {
    if (t_fiber)
        return t_fiber->shared_from_this();
    // Fiber::ptr main_fiber = std::make_shared<Fiber>();
    Fiber::ptr main_fiber(new Fiber());
    SYLAR_ASSERT(t_fiber == main_fiber.get());
    t_threadFiber = std::move(main_fiber);
    return t_fiber->shared_from_this();
}

void Fiber::YieldReady() {
    Fiber::ptr cur = GetThis();
    cur->m_state   = State::READY;
    cur->swapOut();
}

void Fiber::YieldHold() {
    Fiber::ptr cur = GetThis();
    cur->m_state   = State::HOLD;
    cur->swapOut();
}

uint64_t Fiber::TotalFibers() {
    return s_fiber_count;
}

void Fiber::MainFunc() {
    Fiber::ptr cur = GetThis();
    SYLAR_ASSERT(cur);
    try {
        cur->m_cb();
        cur->m_cb    = nullptr;
        cur->m_state = State::TERM;
    } catch (std::exception& e) {
        cur->m_state = State::EXCEPT;
        SYLAR_LOG_ERROR(g_logger)
            << "Fiber Except: " << e.what() << "Fiber Id = " << cur->getId()
            << sylar::BacktraceToString(10, 2, "\t") << '\n';
    } catch (...) {
        cur->m_state = State::EXCEPT;
        SYLAR_LOG_ERROR(g_logger) << "Fiber Except";
    }
    auto raw_pointer = cur.get();
    cur.reset();
    raw_pointer->swapOut();

    SYLAR_ASSERT2(false,
                  "never reach id = " + std::to_string(raw_pointer->getId()));
}

void Fiber::CallerMainFunc() {
    Fiber::ptr cur = GetThis();
    SYLAR_ASSERT(cur);
    try {
        cur->m_cb();
        cur->m_cb    = nullptr;
        cur->m_state = State::TERM;
    } catch (std::exception& e) {
        cur->m_state = State::EXCEPT;
        SYLAR_LOG_ERROR(g_logger)
            << "Fiber Except: " << e.what() << "Fiber Id = " << cur->getId()
            << sylar::BacktraceToString(10, 2, "\t") << '\n';
    } catch (...) {
        cur->m_state = State::EXCEPT;
        SYLAR_LOG_ERROR(g_logger) << "Fiber Except";
    }
    auto raw_pointer = cur.get();
    cur.reset();
    raw_pointer->back();

    SYLAR_ASSERT2(false,
                  "never reach id = " + std::to_string(raw_pointer->getId()));
}

uint64_t Fiber::GetFiberId() {
    if (t_fiber)
        return t_fiber->getId();
    return 0;
}


}  // namespace sylar
