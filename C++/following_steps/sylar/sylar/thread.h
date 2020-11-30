#pragma once
#include <functional>
#include <memory>
#include <pthread.h>
#include <semaphore.h>
#include <string>
#include <atomic>

namespace sylar {

class Semaphore
{
public:
    Semaphore(uint32_t count = 0);
    ~Semaphore();

    void wait();
    void notify();

    Semaphore(const Semaphore&) = delete;
    Semaphore(Semaphore&&)      = delete;
    Semaphore& operator=(const Semaphore&) = delete;

private:
    sem_t m_semaphore;
};

template <typename T>
struct ScopedLockImpl
{
public:
    explicit ScopedLockImpl(T& mutex) : m_mutex{mutex} {
        m_mutex.lock();
        m_locked = true;
    }

    ScopedLockImpl(const ScopedLockImpl&) = delete;
    ScopedLockImpl& operator=(const ScopedLockImpl&) = delete;

    ~ScopedLockImpl() {
        unlock();
    }

    void lock() {
        if (!m_locked) {
            m_mutex.lock();
            m_locked = true;
        }
    }
    void unlock() {
        if (m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    T& m_mutex;
    bool m_locked = false;
};

template <typename T>
struct ReadScopedLockImpl
{
public:
    explicit ReadScopedLockImpl(T& mutex) : m_mutex{mutex} {
        m_mutex.rdlock();
        m_locked = true;
    }

    ReadScopedLockImpl(const ReadScopedLockImpl&) = delete;
    ReadScopedLockImpl& operator=(const ReadScopedLockImpl&) = delete;

    ~ReadScopedLockImpl() {
        unlock();
    }

    void lock() {
        if (!m_locked) {
            m_mutex.rdlock();
            m_locked = true;
        }
    }
    void unlock() {
        if (m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    T& m_mutex;
    bool m_locked = false;
};

template <typename T>
struct WriteScopedLockImpl
{
public:
    explicit WriteScopedLockImpl(T& mutex) : m_mutex{mutex} {
        m_mutex.wrlock();
        m_locked = true;
    }

    WriteScopedLockImpl(const WriteScopedLockImpl&) = delete;
    WriteScopedLockImpl& operator=(const WriteScopedLockImpl&) = delete;


    ~WriteScopedLockImpl() {
        unlock();
    }

    void lock() {
        if (!m_locked) {
            m_mutex.wrlock();
            m_locked = true;
        }
    }
    void unlock() {
        if (m_locked) {
            m_mutex.unlock();
            m_locked = false;
        }
    }

private:
    T& m_mutex;
    bool m_locked = false;
};

class Mutex
{
public:
    typedef ScopedLockImpl<Mutex> Locker;

    Mutex() {
        pthread_mutex_init(&m_mutex, nullptr);
    }

    ~Mutex() {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock() {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock() {
        pthread_mutex_unlock(&m_mutex);
    }

private:
    pthread_mutex_t m_mutex;
};

namespace detail {

    struct NullMutex
    {
    public:
        typedef ScopedLockImpl<NullMutex> Locker;

	NullMutex() = default;
	~NullMutex() = default;

        void lock() {}

        void unlock() {}

    };

    struct NullRWMutex
    {
        typedef ReadScopedLockImpl<NullRWMutex> ReadLock;
        typedef WriteScopedLockImpl<NullRWMutex> WriteLock;

	NullRWMutex() = default;
	~NullRWMutex() = default;

        void rdlock() {}
        void wrlock() {}
        void unlock() {}
    };

}

class RWMutex
{
public:
    typedef ReadScopedLockImpl<RWMutex> ReadLock;
    typedef WriteScopedLockImpl<RWMutex> WriteLock;
    RWMutex() {
        pthread_rwlock_init(&m_lock, nullptr);
    }

    ~RWMutex() {
        pthread_rwlock_destroy(&m_lock);
    }

    void rdlock() {
        pthread_rwlock_rdlock(&m_lock);
    }

    void wrlock() {
        pthread_rwlock_wrlock(&m_lock);
    }

    void unlock() {
        pthread_rwlock_unlock(&m_lock);
    }

private:
    pthread_rwlock_t m_lock;
};

class Spinlock
{
public:
    typedef ScopedLockImpl<Spinlock> Locker;

    Spinlock() {
        pthread_spin_init(&m_spinlock, false);
    }

    ~Spinlock() {
        pthread_spin_destroy(&m_spinlock);
    }

    void lock() {
        pthread_spin_lock(&m_spinlock);
    }

    void unlock() {
        pthread_spin_unlock(&m_spinlock);
    }
private:
    pthread_spinlock_t m_spinlock;
};

class CASLock
{
public:
    typedef  ScopedLockImpl<CASLock> Locker;
    CASLock() {
        m_mutex.clear();
    }

    ~CASLock() {
        
    }

    void lock() {
        while(std::atomic_flag_test_and_set_explicit(&m_mutex, std::memory_order_acquire));
    }

    void unlock() {
        std::atomic_flag_clear_explicit(&m_mutex, std::memory_order_release);
    }
private:
    volatile std::atomic_flag m_mutex;
};

class Thread
{
public:
    typedef std::shared_ptr<Thread> ptr;

    static Thread* GetThis();
    static const std::string& GetName();
    static void SetName(const std::string& name);

    Thread(const Thread& thread) = delete;
    Thread(Thread&& thread)      = delete;
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
    pid_t m_tid        = -1;
    pthread_t m_thread = 0;
    std::function<void()> m_cb;
    std::string m_name;

    Semaphore m_semaphore;
};

}  // namespace sylar
