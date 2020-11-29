#pragma once
#include "thread.h"
#include <memory>
#include <functional>
#include <ucontext.h>


namespace sylar {
class Scheduler;

class Fiber : public std::enable_shared_from_this<Fiber>
{
friend class Scheduler;
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


    /**
     * @brief 获得当前协程id
     */
    uint64_t getId() const {return m_id;}

    /**
     * @brief 获得当前协程运行状态
     */
    State getState() const {
        return m_state;
    }

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

    /**
     * @brief 获得当前活跃协程Id
     * @return 协程Id
     */
    static uint64_t GetFiberId();
private:
    Fiber();

    // 为执行user_caller以及不执行use_caller的构造函数执行初始化动作
    void doInitFiber(size_t stack_size);
    // 重载主要区分是否需要使用use_caller,任何值都可以.
    // user_caller是指给scheduler重排协程执行顺序的时候需要构建的执行栈, 接下来的执行函数会和普通协程使用需求不同(分别对应MainFunc和CallerMainFunc())
    Fiber(std::function<void()> cb, size_t stack_size, bool use_caller);

    static void MainFunc();
    static void CallerMainFunc();

    // 限制给友元使用(目前是scheduler)
    void call();
    void back();
private:
    uint64_t m_id = 0;
    size_t m_stackSize = 0;
    State m_state = State::INIT;
    void* m_stack = nullptr;
    ucontext_t m_ucontext;
    std::function<void()> m_cb;
};
}
