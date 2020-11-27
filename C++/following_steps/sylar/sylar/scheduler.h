#pragma once

#include "fiber.h"
#include "thread.h"
#include <list>
#include <memory>
#include <vector>

namespace sylar {
class Scheduler
{
public:
    typedef std::shared_ptr<Scheduler> ptr;
    typedef Mutex MutexType;

    Scheduler(size_t threads          = 1,
              bool use_caller         = true,
              const std::string& name = "");

    virtual ~Scheduler();

    const std::string& getName() const {
        return m_name;
    }

    static Scheduler* GetThis();

    /**
     * @brief Get the Main Fiber object, 调度器主协程
     *
     * @return Fiber* 协程指针
     */
    static Fiber* GetMainFiber();

    void start();

    void stop();


    template <typename FiberOrCb>
    void schedule(FiberOrCb fc, int thread = -1) {
        bool need_tick = false;
        {
            MutexType::Locker locker(m_mutex);
            need_tick = scheduleNoLock(fc, thread);
        }
        if (need_tick) {
            tickle();
        }
    }

    template <typename InputIterator>
    void schedule(InputIterator begin, InputIterator end) {
        bool need_tickle = false;
        {
            MutexType::Locker locker(m_mutex);
            while (begin != end) {
                need_tickle = scheduleNoLock(fc, thread) || need_tickle;
            }
        }
        if (need_tickle) {
            tickle();
        }
    }

private:
    virtual void tickle();
    void run();
    virtual bool stopping();
    void setThis();

    template <typename FiberOrCb>
    bool scheduleNoLock(FiberOrCb fc, int thread) {
        bool need_tickle = m_fibers.empty();
        FiberAndThread ft(fc, thread);
        if (ft.fiber || ft.cb) {
            m_fibers.push_back(ft);
        }
        return need_tickle;
    }

    struct FiberAndThread
    {
        Fiber::ptr fiber;
        std::function<void()> cb;
        int thread_id;

        FiberAndThread(Fiber::ptr f, int _thread_id)
            : fiber(f), thread_id(_thread_id) {}

        FiberAndThread(Fiber::ptr f, int _thread_id) : thread_id(_thread_id) {
            fiber.swap(*f);
        }

        FiberAndThread(std::function<void()> f, int _thread_id)
            : cb(f), thread_id(_thread_id) {}

        FiberAndThread(std::function<void()>* f, int _thread_id)
            : thread_id(_thread_id) {
            cb.swap(*f);
        }

        FiberAndThread() : thread_id(-1) {}

        void reset() {
            fiber     = nullptr;
            cb        = nullptr;
            thread_id = -1;
        }
    };

private:
    MutexType m_mutex;
    std::vector<Thread::ptr> m_threads;
    std::list<> m_fibers;
    Fiber::ptr m_rootFiber;
    std::string m_name;

protected:
    std::vector<int> m_threadIds{};
    size_t m_threadCount       = 0;
    size_t m_activeThreadCount = 0;
    size_t m_idleThradCount    = 0;
    bool m_stopping            = true;
    bool m_autoStop            = false;
    int m_rootThread           = 0;
};
}  // namespace sylar
