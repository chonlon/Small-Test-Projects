#pragma once

#include "thread.h"
#include <memory>
#include <set>


namespace sylar {
class TimerManager;

class Timer : public std::enable_shared_from_this<Timer>
{
    friend class TimerManager;

public:
    typedef std::shared_ptr<Timer> ptr;

private:
    struct Comparator
    {
        bool operator()(const Timer::ptr& lhs, const Timer::ptr& rhs) const;
    };

    Timer(uint64_t ms,
          std::function<void()> cb,
          bool is_recurring,
          TimerManager* manager);

private:
private:
    bool m_recurring = false;  //是否循环定时
    uint64_t m_ms    = 0;      // 执行周期
    uint64_t m_next  = 0;      // 精确执行时间
    std::function<void()> m_cb;
    TimerManager* m_manager = nullptr;
};


class TimerManager
{
    friend class Timer;

public:
    typedef RWMutex RWMutexType;

    TimerManager();
    virtual ~TimerManager();
    Timer::ptr addTimer(uint64_t ms,
                        std::function<void()> cb,
                        bool recurring = false);
    Timer::ptr addConditionTimer(uint64_t ms,
                                 std::function<void()> cb,
                                 std::weak_ptr<void> weak_cond,
                                 bool recurring = false);

protected:
    virtual void onTimerInsertedAtFront() = 0;
private:
    RWMutexType m_mutex;
    std::set<Timer::ptr, Timer::Comparator> m_timers;
};
}  // namespace sylar