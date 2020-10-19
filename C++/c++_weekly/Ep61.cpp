#include <thread>
#include <future>
#include <iostream>

int main() {
    auto l = [] () {
        static auto val = 0;
        //thread_local auto val = 0;
        //static std::atomic<int> val{0};

        return val++;
    };

    auto l2 = l;
    //l();

    auto f = std::async(std::launch::async, l);
    {// 使用sleepfor或者get都是阻塞当前线程让住线程先执行完成避免数据竞争
     // threadlocal则是将变量存到thread的栈中, 而不是静态变量区

        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        //f.get();
    }


    l2();
    l2();
    l();
    l();

    std::cout << l();
    return 0;
}