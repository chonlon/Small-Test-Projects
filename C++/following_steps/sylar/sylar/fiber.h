#pragma once
#include "thread.h"
#include <memory>
#include <functional>
#include <ucontext.h>


namespace sylar {
class Fiber : public std::enable_shared_from_this<Fiber>
{
public:
    typedef std::shared_ptr<Fiber> ptr;

    enum class State
    {
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY,
        EXCEPT
    };


    /**
     * \brief 构造协程, 非主协程
     * \param cb 协程函数
     * \param stack_size 栈空间大小
     */
    Fiber(std::function<void()> cb, size_t stack_size = 0);
    ~Fiber();


    /**
     * \brief 重置协程函数并重置状态; 一般当前协程status为INIT, TERM
     * \param cb 协程函数
     */
    void reset(std::function<void()> cb);
    
    /**
     * \brief 切换到当前协程执行
     */
    void swapIn();

    /**
     * \brief 将当前协程切换到后台, 让出执行权.
     */
    void swapOut();

    uint64_t getId() const {return m_id;}

public:

    /**
     * \brief 设置当前协程
     * \param fiber 当前协程指针, 不为空.
     */
    static void SetThis(Fiber* fiber);

    /**
     * \brief 获取当前协程
     * \return 当前协程
     */
    static Fiber::ptr GetThis();

    
    /**
     * \brief 协程切换到后台并设置成ready状态
     */
    static void YieldReady();
    

    /**
     * \brief 协程切换到后台并设置成Hold状态.
     */
    static void YieldHold();

    /**
     * \brief 获取总协程数
     * \return 总协程数
     */
    static uint64_t TotalFibers();

    static void MainFunc();

    static uint64_t GetFiberId();
private:
    Fiber();
private:
    uint64_t m_id = 0;
    size_t m_stackSize = 0;
    State m_state = State::INIT;
    void* m_stack = nullptr;
    ucontext_t m_ucontext;
    std::function<void()> m_cb;
};
}
