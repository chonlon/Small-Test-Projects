#include "scheduler.h"
#include "log.h"
#include "macro.h"


namespace sylar {
static Logger::ptr g_logger = SYLAR_LOG_NAME("system");

static thread_local Scheduler* t_scheduler = nullptr;
static thread_local Fiber* t_fiber         = nullptr;

Scheduler::Scheduler(size_t threads, bool use_caller, const std::string& name) : m_name(name) {
    SYLAR_ASSERT(threads > 0)
    if (use_caller) {
        sylar::Fiber::GetThis();
        --threads;

        SYLAR_ASSERT(GetThis() == nullptr)
        t_scheduler = this;

        m_rootFiber.reset(new Fiber(std::bind(&Scheduler::run, this), 0, true));
        Thread::SetName(m_name);
        t_fiber      = m_rootFiber.get();
        m_rootThread = sylar::GetThreadId();
        m_threadIds.push_back(m_rootThread);
    } else {
        m_rootThread = -1;
    }
    m_threadCount = threads;
}

Scheduler::~Scheduler() {
    SYLAR_ASSERT(m_stopping)
    if (GetThis() == this) {
        t_scheduler = nullptr;
    }
}

Scheduler* Scheduler::GetThis() {
    return t_scheduler;
}

Fiber* Scheduler::GetMainFiber() {
    return t_fiber;
}

void Scheduler::start() {
    MutexType::Locker locker(m_mutex);
    if (!m_stopping) {
        return;
    }
    m_stopping = false;
    SYLAR_ASSERT(m_threads.empty())
    m_threads.reserve(m_threadCount);
    m_threadIds.reserve(m_threadCount);
    for (size_t i = 0; i < m_threadCount; ++i) {
        m_threads.emplace_back(
            std::make_shared<Thread>(std::bind(&Scheduler::run, this),
                                     m_name + '_' + std::to_string(i)));
        m_threadIds.push_back(m_threads[i]->getId());
    }
    locker.unlock();
    //    if (m_rootFiber) {
    //        m_rootFiber->call();
    //        // m_rootFiber->swapIn();
    //        SYLAR_LOG_INFO(g_logger)
    //            << "call out" << static_cast<int>(m_rootFiber->getState());
    //    }
}

void Scheduler::stop() {
    m_autoStop = true;
    if (m_rootFiber && m_threadCount == 0 &&
        (m_rootFiber->getState() == Fiber::State::TERM ||
         m_rootFiber->getState() == Fiber::State::INIT)) {
        SYLAR_LOG_INFO(g_logger) << this << " stopped";
        m_stopping = true;
        if (stopping()) {
            return;
        }
    }

    // bool exit_on_this_fiber = false;
    if (m_rootThread != -1) {
        SYLAR_ASSERT(GetThis() == this)


    } else {
        SYLAR_ASSERT(GetThis() != this);
    };

    m_stopping = true;
    for (size_t i = 0; i < m_threadCount; ++i) {
        tickle();
    }

    if (m_rootFiber) {
        tickle();
    }

    if (m_rootFiber) {
//        while (!stopping()) {
//            if (m_rootFiber->getState() == Fiber::State::TERM ||
//                m_rootFiber->getState() == Fiber::State::EXCEPT) {
//                m_rootFiber.reset(
//                    new Fiber(std::bind(&Scheduler::run, this), 0, true));
//                SYLAR_LOG_INFO(g_logger) << " root fiber is term, reset";
//                t_fiber = m_rootFiber.get();
//            }
//            m_rootFiber->call();
//        }
        if(!stopping()) {
            m_rootFiber->call();
        }
    }

    std::vector<Thread::ptr> thrs;
    {
        MutexType::Locker locker(m_mutex);
        thrs.swap(m_threads);
    }
    for(auto &i : thrs) {
        i->join();
    }

    if (stopping()) {
        return;
    }
    //    if (exit_on_this_fiber) {
    //    }
}

void Scheduler::run() {
    SYLAR_LOG_INFO(g_logger) << "run";
    setThis();

    if (GetThreadId() != m_rootThread) {
        t_fiber = Fiber::GetThis().get();
    }

    Fiber::ptr idle_fiber =
        std::make_shared<Fiber>(std::bind(&Scheduler::idle, this));
    Fiber::ptr cb_fiber;
    FiberAndThread ft;
    while (true) {
        ft.reset();
        bool tickle_me = false;
        bool is_active = false;
        {
            MutexType::Locker locker(m_mutex);
            auto it = m_fibers.begin();
            while (it != m_fibers.end()) {
                if (it->thread_id != -1 &&
                    it->thread_id != sylar::GetThreadId()) {
                    ++it;
                    tickle_me = true;
                    continue;
                }
                SYLAR_ASSERT(it->fiber || it->cb)
                if (it->fiber && it->fiber->getState() == Fiber::State::EXEC) {
                    ++it;
                    continue;
                }

                ft = *it;
                m_fibers.erase(it);
                ++m_activeThreadCount;
                is_active = true;
                break;
            }
        }
        if (tickle_me) {
            tickle();
        }

        if (ft.fiber && ft.fiber->getState() != Fiber::State::TERM &&
            ft.fiber->getState() != Fiber::State::EXCEPT) {

            ft.fiber->swapIn();
            --m_activeThreadCount;
            if (ft.fiber->getState() == Fiber::State::READY) {
                schedule(ft.fiber);
            } else if (ft.fiber->getState() != Fiber::State::TERM &&
                       ft.fiber->getState() != Fiber::State::EXCEPT) {
                ft.fiber->m_state = Fiber::State::HOLD;
            }
            ft.reset();
        } else if (ft.cb) {
            if (cb_fiber) {
                cb_fiber->reset(ft.cb);
            } else {
                cb_fiber.reset(new Fiber(ft.cb));
            }
            ft.reset();
            //++m_activeThreadCount;
            cb_fiber->swapIn();
            --m_activeThreadCount;
            if (cb_fiber->getState() == Fiber::State::READY) {
                schedule(cb_fiber);
                cb_fiber.reset();
            } else if (cb_fiber->getState() == Fiber::State::TERM ||
                       cb_fiber->getState() == Fiber::State::EXCEPT) {
                cb_fiber->reset(nullptr);
            } else {
                cb_fiber->m_state = Fiber::State::HOLD;
                cb_fiber.reset();
            }
        } else {
            if(is_active) {
                --m_activeThreadCount;
                continue;
            }
            if (idle_fiber->getState() == Fiber::State::TERM) {
                SYLAR_LOG_INFO(g_logger) << "idle fiber term";
                // continue;
                break;
            }

            ++m_idleThreadCount;
            idle_fiber->swapIn();
            if (idle_fiber->getState() != Fiber::State::TERM &&
                idle_fiber->getState() != Fiber::State::EXCEPT) {
                idle_fiber->m_state = Fiber::State::HOLD;
            }
            --m_idleThreadCount;
        }
    }
}
void Scheduler::tickle() {
    SYLAR_LOG_INFO(g_logger) << "tickle";
}


bool Scheduler::stopping() {
    MutexType::Locker locker(m_mutex);
    return m_autoStop && m_stopping && m_fibers.empty() &&
        m_activeThreadCount == 0;
}
void Scheduler::idle() {
    SYLAR_LOG_INFO(g_logger) << "idle";
    while(!stopping()) {
        sylar::Fiber::YieldHold();
    }
}
void Scheduler::setThis() {
    t_scheduler = this;
}

}  // namespace sylar
