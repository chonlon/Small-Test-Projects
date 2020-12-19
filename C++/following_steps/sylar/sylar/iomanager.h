#pragma once

#include "scheduler.h"
#include "timer.h"
#include <ostream>

namespace sylar {
class IOManager : public Scheduler, public TimerManager
{
public:
    typedef std::shared_ptr<IOManager> ptr;
    typedef RWMutex RWMutexType;

    enum Event
    {
        NONE  = 0x0,
        READ  = 0x1, //EPOLLIN
        WRITE = 0x4, //EPOLLOUT
    };


private:
    struct FdContext
    {
        typedef Mutex MutexType;
        struct EventContext
        {
            Scheduler* scheduler = nullptr;  //事件执行的scheduler
            std::shared_ptr<Fiber> fiber;    // 事件的协程
            std::function<void()> cb;        // 事件的回调

        };
        void triggerEvent(Event event);
        EventContext& getContext(Event event);
        static void resetContext(EventContext& context);

        int fd = 0;                  // 事件关联句柄
        EventContext read;           //读事件
        EventContext write;          //写事件
        Event events = Event::NONE;  //已经注册的事件
        MutexType mutex;
    };

public:
    IOManager(size_t threads = 1, bool user_caller = true, const std::string& name = "");
    virtual ~IOManager();

    // 0. success, -1 error
    int addEvent(int fd, Event event, std::function<void()> = nullptr);
    bool delEvent(int fd, Event event);
    bool cancelEvent(int fd, Event event);
    bool cancelAll(int fd);
    static IOManager* GetThis();

protected:
    void tickle() override;
    bool stopping() override;
    void idle() override;
    void onTimerInsertedAtFront() override;
    bool stopping(int& timeout);
private:
    void contextResize(size_t size);

private:
    int m_ep_fd = 0;
    int m_tickleFds[2]{};
    std::atomic<size_t> m_pendingEventCount{0};
    RWMutexType m_mutex;
    std::vector<FdContext*> m_fdContexts;
};
}  // namespace sylar