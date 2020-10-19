// MemoryOrder.cpp: 定义应用程序的入口点。
//

#include "MemoryOrder.h"

using namespace std;

enum class TestType
{
    Relaxed,
    Release_Acquire,
    Release_Consume,
    Acq_Rel,
    Seq_Cst
};

class
{
    int a;
};

int f()
{
    return 0;
}

int main()
{
    constexpr TestType test     = TestType::Release_Acquire;
    constexpr int time_sleep_ms = 500;
    int av_global               = 0;
    std::function<void(void)> t1f{};
    std::function<void(void)> t2f{};

    std::atomic<int> a{0}, b{0};

    auto setInner = [time_sleep_ms ,&av_global, &a, &b](
        int bv,
        std::memory_order ma,
        std::memory_order mb,
        int c = 0,
        int d = 0)
    {
        for (int i = 0; i < 10; ++i) {
            a.store(av_global, ma);
            b.store(bv + i, mb);
            std::this_thread::sleep_for(
                std::chrono::milliseconds(time_sleep_ms));
            av_global += 1;
        }
    };

    auto readInner = [time_sleep_ms, &av_global, &a, &b](
        std::memory_order ma,
        std::memory_order mb)
    {
        for (int i = 0; i < 10; ++i) {
            while (a.load(ma) != av_global)
                std::this_thread::sleep_for(std::chrono::milliseconds(0));
            std::cout << "b: " << b.load(mb) << '\n';
            std::this_thread::sleep_for(
                std::chrono::milliseconds(time_sleep_ms));
        }
    };

    if constexpr (test == TestType::Relaxed) {
        printDividing(" TestType::Relaxed ");

        t1f = [&setInner]()
        {
            setInner(
                100,
                std::memory_order_relaxed,
                std::memory_order_relaxed);
        };

        t2f = [&readInner]()
        {
            readInner(std::memory_order_relaxed,
                      std::memory_order_relaxed);
        };

        // 这个case中， 每次b的写入都可能发生再a的每次写入之前。
    } else if constexpr (test == TestType::Release_Acquire) {
        printDividing(" TestType::Release_Acquire ");

        t1f = [&setInner]()
        {
            setInner(100, std::memory_order_release, std::memory_order_relaxed);
        };

        t2f = [&readInner]()
        {
            readInner(std::memory_order_acquire, std::memory_order_relaxed);
        };
        // 在这个case中, 每次b的写入必定发生再a写入之后.
    } else if constexpr (test == TestType::Release_Consume) {
        printDividing(" TestType::Release_Acquire ");

        t1f = [&setInner]()
        {
            setInner(100, std::memory_order_release, std::memory_order_relaxed);
        };

        t2f = [&readInner]()
        {
            readInner(std::memory_order_consume, std::memory_order_relaxed);
        };
        // 这个case中， 每次b的写入都可能发生再a的每次写入之前。
        // 内存控制只对[a]内存相关操作有效
    }

    std::thread t1{t1f};
    std::thread t2{t2f};

    t1.join();
    t2.join();

    return 0;
}
