#pragma once

#include "fiber.h"
#include "thread.h"
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
        if(need_tick) {
            tickle();
        }
    }

    template <typename  InputIterator>
    void schedule(InputIterator begin, InputIterator end) {
        bool need_tickle = false;
        {
            MutexType::Locker locker(m_mutex);
            while(begin != end) {
                need_tickle = scheduleNoLock(fc, thread) || need_tickle;
            }
        }
        if (need_tick) {
            tickle();
        }
    }
private:
    virtual void tickle();

    template <typename FiberOrCb>
    bool scheduleNoLock(FiberOrCb fc, int thread) {
        bool need_tickle = m_fiber.empty();
        FiberAndThread ft(fc, thread);
        if (ft.fiber || ft.cb) {
            m_fibers.push_back(ft);
        }
        return needle_tickle;
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

        FiberAndThread() : thread(-1) {}
        void reset() {
            fiber  = nullptr;
            cb     = nullptr;
            thread = -1;
        }
    };

private:
    MutexType m_mutex;
    std::vector<Thread::ptr> m_threads;
    std::list<> m_fibers;
    std::string m_name;
};
}  // namespace sylar
