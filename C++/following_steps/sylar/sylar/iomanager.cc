#include "iomanager.h"
#include "log.h"
#include "macro.h"
#include "sys/epoll.h"

#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
namespace sylar {
static auto g_logger   = SYLAR_LOG_NAME("system");


IOManager::IOManager(size_t threads, bool user_caller, const std::string& name)
    : Scheduler(threads, user_caller, name) {
    m_ep_fd = epoll_create(5000);
    SYLAR_ASSERT(m_ep_fd > 0)
    int rt = pipe(m_tickleFds);
    SYLAR_ASSERT(rt == 0)
    epoll_event event;
    memset(&event, 0, sizeof(epoll_event));
    event.events  = EPOLLIN | EPOLLET;
    event.data.fd = m_tickleFds[0];
    rt            = fcntl(m_tickleFds[0], F_SETFL, O_NONBLOCK);
    SYLAR_ASSERT(rt == 0)
    rt = epoll_ctl(m_ep_fd, EPOLL_CTL_ADD, m_tickleFds[0], &event);
    SYLAR_ASSERT(rt == 0)

    contextResize(32);

    start();
    // epoll_wait()
}

IOManager::~IOManager() {
    stop();
    close(m_ep_fd);
    close(m_tickleFds[0]);
    close(m_tickleFds[1]);
    for (size_t i = 0; i < m_fdContexts.size(); ++i) {
        if (m_fdContexts[i]) {
            delete m_fdContexts[i];
        }
    }
}

int IOManager::addEvent(int fd,
                        IOManager::Event event,
                        std::function<void()> cb) {
    FdContext* fd_ctx = nullptr;
    RWMutexType::WriteLock locker(m_mutex);
    if (m_fdContexts.size() > static_cast<size_t>(fd)) {
        fd_ctx = m_fdContexts[fd];
        locker.unlock();
    } else {
        locker.unlock();
        RWMutexType::WriteLock locker2(m_mutex);
        contextResize(static_cast<size_t>(
            static_cast<double>(fd) * 1.5));
        fd_ctx = m_fdContexts[fd];
    }
    FdContext::MutexType::Locker locker2(fd_ctx->mutex);
    if (fd_ctx->events & event) {
        SYLAR_LOG_ERROR(g_logger)
            << "addEvent assert fd = " << fd << " event = " << event
            << " fd_ctx event = " << static_cast<int>(fd_ctx->events);
        SYLAR_ASSERT(!(fd_ctx->events & event))
    }
    int op = fd_ctx->events ? EPOLL_CTL_MOD : EPOLL_CTL_ADD;
    epoll_event epevent;
    epevent.events =
        EPOLLET | static_cast<EPOLL_EVENTS>(fd_ctx->events | event);
    epevent.data.ptr = fd_ctx;
    int rt           = epoll_ctl(m_ep_fd, op, fd, &epevent);
    if (rt) {
        SYLAR_LOG_ERROR(g_logger)
            << "epoll_ctl(" << m_ep_fd << ", " << op << "," << fd << ","
            << epevent.events << "): " << rt << " (" << errno << ")"
            << " (" << strerror(errno) << ")";
        return -1;
    }
    ++m_pendingEventCount;
    fd_ctx->events = static_cast<Event>(fd_ctx->events | event);
    FdContext::EventContext& event_context = fd_ctx->getContext(event);
    SYLAR_ASSERT(!event_context.scheduler && !event_context.fiber &&
                 !event_context.cb);
    event_context.scheduler = Scheduler::GetThis();
    if (cb) {
        event_context.cb.swap(cb);
    } else {
        event_context.fiber = Fiber::GetThis();
        SYLAR_ASSERT(event_context.fiber->getState() == Fiber::State::EXEC);
    }
    return 0;
}

bool IOManager::delEvent(int fd, IOManager::Event event) {
    RWMutexType::ReadLock locker(m_mutex);
    if (m_fdContexts.size() <= static_cast<size_t>(fd)) {
        return false;
    }
    FdContext* fd_ctx = m_fdContexts[fd];
    locker.unlock();
    FdContext::MutexType::Locker locker2(fd_ctx->mutex);
    if (!(fd_ctx->events & event)) {
        return false;
    }

    Event new_events = static_cast<Event>(fd_ctx->events & ~event);
    int op           = new_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
    epoll_event ep_event{};
    ep_event.events   = EPOLLET | static_cast<EPOLL_EVENTS>(new_events);
    ep_event.data.ptr = fd_ctx;

    int rt = epoll_ctl(m_ep_fd, op, fd, &ep_event);
    if (rt) {
        SYLAR_LOG_ERROR(g_logger)
            << "epoll_ctl(" << m_ep_fd << ", " << op << "," << fd << ","
            << ep_event.events << "): " << rt << " (" << errno << ")"
            << " (" << strerror(errno) << ")";
        return false;
    }

    --m_pendingEventCount;
    fd_ctx->events                     = new_events;
    FdContext::EventContext& event_ctx = fd_ctx->getContext(event);
    fd_ctx->resetContext(event_ctx);
    return true;
}
bool IOManager::cancelEvent(int fd, IOManager::Event event) {
    RWMutexType::ReadLock locker(m_mutex);
    if (m_fdContexts.size() <= static_cast<size_t>(fd)) {
        return false;
    }
    FdContext* fd_ctx = m_fdContexts[fd];
    locker.unlock();
    FdContext::MutexType::Locker locker2(fd_ctx->mutex);
    if (!(fd_ctx->events & event)) {
        return false;
    }

    Event new_events = static_cast<Event>(fd_ctx->events & ~event);
    int op           = new_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
    epoll_event ep_event{};
    ep_event.events   = EPOLLET | static_cast<EPOLL_EVENTS>(new_events);
    ep_event.data.ptr = fd_ctx;

    int rt = epoll_ctl(m_ep_fd, op, fd, &ep_event);
    if (rt) {
        SYLAR_LOG_ERROR(g_logger)
            << "epoll_ctl(" << m_ep_fd << ", " << op << "," << fd << ","
            << ep_event.events << "): " << rt << " (" << errno << ")"
            << " (" << strerror(errno) << ")";
        return false;
    }

    fd_ctx->triggerEvent(event);

    --m_pendingEventCount;
    return true;
}
bool IOManager::cancelAll(int fd) {
    RWMutexType::ReadLock locker(m_mutex);
    if (m_fdContexts.size() <= static_cast<size_t>(fd)) {
        return false;
    }
    FdContext* fd_ctx = m_fdContexts[fd];
    locker.unlock();
    FdContext::MutexType::Locker locker2(fd_ctx->mutex);
    if (!fd_ctx->events) {
        return false;
    }


    int op = EPOLL_CTL_DEL;
    epoll_event ep_event{};
    ep_event.events   = 0;
    ep_event.data.ptr = fd_ctx;

    int rt = epoll_ctl(m_ep_fd, op, fd, &ep_event);
    if (rt) {
        SYLAR_LOG_ERROR(g_logger)
            << "epoll_ctl(" << m_ep_fd << ", " << op << "," << fd << ","
            << ep_event.events << "): " << rt << " (" << errno << ")"
            << " (" << strerror(errno) << ")";
        return false;
    }

    if (fd_ctx->events & Event::READ) {

        fd_ctx->triggerEvent(READ);
        --m_pendingEventCount;
    }
    if (fd_ctx->events & Event::WRITE) {

        fd_ctx->triggerEvent(WRITE);
        --m_pendingEventCount;
    }

    SYLAR_ASSERT(fd_ctx->events == 0)
    return true;
}
IOManager* IOManager::GetThis() {
    return dynamic_cast<IOManager*>(Scheduler::GetThis());
}

void IOManager::tickle() {
    if (hasIdleThreads()) {
        return;
    }

    ssize_t rt = write(m_tickleFds[1], "T", 1);
    SYLAR_ASSERT(rt == 1)
}
bool IOManager::stopping() {
    return Scheduler::stopping() && m_pendingEventCount == 0;
}
void IOManager::idle() {
//奇怪的用法, 再者用unique_ptr也比这强吧.
//    epoll_event* events = new epoll_event[64];
//
//    std::shared_ptr<epoll_event> shared_events(
//        events, [](epoll_event* ptr) { delete[] ptr; });

//    epoll_event* events = new epoll_event[64];
//    std::unique_ptr<epoll_event[]> shared_events(events);

    epoll_event events[64];

    while (true) {
        if (stopping()) {
            SYLAR_LOG_INFO(g_logger)
                << "name=" << getName() << " idle stopping exit";
            break;
        }
        int rt = 0;
        do {
            constexpr int MAX_TIMEOUT = 5000;
            rt = epoll_wait(m_ep_fd, events, 64, MAX_TIMEOUT);

            if (rt < 0 && errno == EINTR) {

            } else {
                break;
            }
        } while (true);

        for (int i = 0; i < rt; ++i) {
            epoll_event& event = events[i];
            if (event.data.fd == m_tickleFds[0]) {
                uint8_t dummy;
                while (read(m_tickleFds[0], &dummy, 1) == 1)
                    ;
                continue;
                // 这里是不是应该swapOut来处理其他事件, 不然的话, 切换不到Scheduler的run去执行调度吧.
            }

            FdContext* fd_context = static_cast<FdContext*>(events[i].data.ptr);
            FdContext::MutexType::Locker locker(fd_context->mutex);
            if (event.events & (EPOLLERR | EPOLLHUP)) {
                event.events |= EPOLLIN | EPOLLOUT;
            }
            int real_events = NONE;
            if (event.events & EPOLLIN) {
                real_events |= READ;
            }
            if (event.events & EPOLLOUT) {
                real_events |= WRITE;
            }

            if ((fd_context->events & real_events) == NONE) {
                continue;
            }

            int left_events = (fd_context->events & ~real_events);
            int op          = left_events ? EPOLL_CTL_MOD : EPOLL_CTL_DEL;
            event.events    = EPOLLET | left_events;
            int rt2         = epoll_ctl(m_ep_fd, op, fd_context->fd, &event);
            if (rt2) {
                SYLAR_LOG_ERROR(g_logger)
                    << "epoll_ctl(" << m_ep_fd << ", " << op << "," << fd_context
                    << "," << event.events << "): " << rt2 << " (" << errno << ")"
                    << " (" << strerror(errno) << ")";
                continue;
            }

            if (real_events & READ) {
                fd_context->triggerEvent(READ);
                --m_pendingEventCount;
            }
            if (real_events & WRITE) {
                fd_context->triggerEvent(WRITE);
                --m_pendingEventCount;
            }

        }
        Fiber::ptr cur = Fiber::GetThis();
        auto raw_ptr = cur.get();
        cur.reset();
        raw_ptr->swapOut();
    }


}
void IOManager::contextResize(size_t size) {
    m_fdContexts.resize(size);
    for (size_t i = 0; i < m_fdContexts.size(); ++i) {
        m_fdContexts[i]     = new FdContext;
        m_fdContexts[i]->fd = static_cast<int>(i);
    }
}


void IOManager::FdContext::triggerEvent(Event event) {
    SYLAR_ASSERT(events & event)
    events            = static_cast<Event>(events & ~event);
    EventContext& ctx = getContext(event);
    if (ctx.cb) {
        ctx.scheduler->schedule(&ctx.cb);
    } else {
        ctx.scheduler->schedule(&ctx.fiber);
    }
    ctx.scheduler = nullptr;
}
IOManager::FdContext::EventContext& IOManager::FdContext::getContext(
    IOManager::Event event) {
    switch (event) {
        case READ:
            return read;
        case WRITE:
            return write;
        case NONE:
        default:
            SYLAR_ASSERT2(false, "getContext")
    }
}
void IOManager::FdContext::resetContext(
    IOManager::FdContext::EventContext& context) {
    context.scheduler = nullptr;
    context.fiber.reset();
    context.cb = nullptr;
}
}  // namespace sylar