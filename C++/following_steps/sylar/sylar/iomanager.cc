#include "iomanager.h"
#include "sys/epoll.h"
#include "macro.h"
#include "log.h"

#include <fcntl.h>
#include <unistd.h>
namespace sylar {
static auto g_logger = SYLAR_LOG_NAME("system");
IOManager::IOManager() {}

IOManager::IOManager(size_t threads, bool user_caller, const std::string& name)
    : Scheduler(threads, user_caller, name) {
    m_ep_fd = epoll_create(5000);
    SYLAR_ASSERT(m_ep_fd > 0);
    int rt = pipe(m_tickleFds);
    SYLAR_ASSERT(rt);
    epoll_event event;
    memset(&event, 0, sizeof(epoll_event));
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = m_tickleFds[0];
    rt = fcntl(m_tickleFds[0], F_SETFL, O_NONBLOCK);
    SYLAR_ASSERT(rt);
    rt = epoll_ctl(m_ep_fd, EPOLL_CTL_ADD, m_tickleFds[0], &event);
    SYLAR_ASSERT(rt);

    m_fdContexts.resize(64);

    start();
    //epoll_wait()
}

IOManager::~IOManager() {
    stop();
    close(m_ep_fd);
    close(m_tickleFds[0]);
    close(m_tickleFds[1]);
    for(size_t i = 0; i < m_fdContexts.size(); ++i) {
        if(m_fdContexts[i]) {
            delete m_fdContexts[i];
        }
    }
}

int IOManager::addEvent(int fd, IOManager::Event event, std::function<void()>) {
    FdContext* fd_ctx = nullptr;
    RWMutexType::WriteLock locker(m_mutex);
    if(m_fdContexts.size() > fd) {
        fd_ctx = m_fdContexts[fd];
        locker.unlock();
    } else {
        locker.unlock();
        RWMutexType::WriteLock locker2(m_mutex);
        contextResize(static_cast<size_t>(m_fdContexts.size() * 1.5));
        fd_ctx = m_fdContexts[fd];
    }
    FdContext::MutexType::Locker locker2(fd_ctx->mutex);
    if(fd_ctx->events & event) {
        SYLAR_LOG_ERROR(g_logger) << "state error";
    }
}

bool IOManager::delEvent(int fd, IOManager::Event event) {
    return false;
}
bool IOManager::cancelEvent(int fd, IOManager::Event event) {
    return false;
}
bool IOManager::cancelAll(int fd) {
    return false;
}
IOManager* IOManager::GetThis() {
    return nullptr;
}

void IOManager::tickle() {}
bool IOManager::stopping() {
    return false;
}
void IOManager::idle() {}
void IOManager::contextResize(size_t size) {
    m_fdContexts.resize(size);
    for(size_t i = 0; i < m_fdContexts.size(); ++i) {
        m_fdContexts[i] = new FdContext;
        m_fdContexts[i]->fd = static_cast<int>(i);
    }
}


}