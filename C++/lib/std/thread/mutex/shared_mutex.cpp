#include <shared_mutex>
#include <mutex>
#include <thread>
#include <chrono>
#include <iostream>

int main() {

    std::shared_mutex rw_mutex;
    auto read_fun = [&rw_mutex] (std::chrono::time_point<std::chrono::steady_clock>& tp) {
        std::shared_lock lock{rw_mutex};
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        tp = std::chrono::steady_clock::now();
    };

    auto write_fun = [&rw_mutex] (std::chrono::time_point<std::chrono::steady_clock>& tp) {
        std::unique_lock lock{rw_mutex};
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        tp = std::chrono::steady_clock::now();
    };

    {

        std::chrono::time_point<std::chrono::steady_clock> r_tp;
        std::chrono::time_point<std::chrono::steady_clock> w_tp;
        std::thread tr{read_fun, std::ref(r_tp)};
        // ensure write will exec after read
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::thread tw{write_fun, std::ref(w_tp)};

        tr.join();
        tw.join();

        // 如果输出显示~200说明写线程获取锁的时间和读线程释放锁的时间一样, 也就是shared_mutex锁住的时候只有shared_mutex能获取锁
        std::cout << "1: cost ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(w_tp - r_tp).count() << '\n';
    }

    {
        std::chrono::time_point<std::chrono::steady_clock> r_tp_1;
        std::chrono::time_point<std::chrono::steady_clock> r_tp_2;
        std::thread tr{read_fun, std::ref(r_tp_1)};

        std::thread tr2{read_fun, std::ref(r_tp_2)};

        tr.join();
        tr2.join();

        std::cout << "1: cost ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(r_tp_1 - r_tp_2).count() << '\n';
    }
}