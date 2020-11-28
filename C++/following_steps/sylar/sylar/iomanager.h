#pragma once

#include "scheduler.h"
#include <ostream>

namespace sylar {
class IOManager : public Scheduler
{
public:
    typedef std::shared_ptr<IOManager> ptr;
    typedef RWMutex RWMutexType;

    enum class Event
    {
        NONE  = 0x0,
        READ  = 0x1,
        WRITE = 0x2,
    };



private:
    struct FdContext{
        typedef Mutex MutexType;
        struct EventContext{
            Scheduler* scheduler = nullptr; //事件执行的scheduler
            std::shared_ptr<Fiber> fiber; // 事件的协程
            std::function<void()> cb; // 事件的回调
        };
        int fd = 0; // 事件关联句柄
        EventContext read; //读事件
        EventContext write; //写事件
        Event events = Event::NONE; //已经注册的事件
        MutexType mutex;
    };

public:
    IOManager();
    IOManager(size_t threads, bool user_caller, const std::string& name = "");
    virtual ~IOManager();

    //1. success, 0 retry, -1 error
    int addEvent(int fd, Event event, std::function<void()> = nullptr);
    bool delEvent(int fd, Event event);
    bool cancelEvent(int fd, Event event);
    bool cancelAll(int fd);
    static IOManager* GetThis();

protected:
    void tickle() override;
    bool stopping() override;
    void idle() override;

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