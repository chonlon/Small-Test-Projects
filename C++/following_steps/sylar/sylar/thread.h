#pragma once
#include <functional>
#include <memory>
#include <pthread.h>
#include <string>


namespace sylar {

class Thread
{
public:
    typedef std::shared_ptr<Thread> ptr;

    static Thread* GetThis();
    static const std::string& GetName();
    static void SetName(const std::string& name);

    Thread(const Thread& thread) = delete;
    Thread(Thread&& thread) = delete;
    Thread& operator=(const Thread& thread) = delete;

    Thread(const std::function<void()>& cb, const std::string& name);

    ~Thread();

    auto getName() const -> std::string {
        return m_name;
    }

    auto setName(const std::string& name) -> void {
        this->m_name = name;
    }

    auto getId() const -> pid_t {
        return m_tid;
    }

    void join();
    void detach();

private:
    static void* run(void* arg);

private:

    pid_t m_tid = -1;
    pthread_t m_thread = 0;
    std::function<void()> m_cb;
    std::string m_name;
};

}  // namespace sylar
