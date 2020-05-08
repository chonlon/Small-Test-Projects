#include <chrono>
#include <iostream>
#include <thread>
#include <windows.h>
using namespace std;
// https://stackoverflow.com/questions/13397571/precise-thread-sleep-needed-max-1ms-error
// 可以尝试自旋锁.

using Clock = std::chrono::high_resolution_clock;
template <typename T>
using duration = std::chrono::duration<T>;

// 一个简单的跨平台的延时,
// 不过很占用很多cpu(占用一个核的cpu), 精度很高
void sleep_foo(double dt) {
    constexpr duration<double> MinSleepDuration(
        0);
    Clock::time_point start = Clock::now();
    while (duration<double>(Clock::now() - start)
               .count() < dt) {
        std::this_thread::sleep_for(
            MinSleepDuration);
    }
}

// windows 下延时, 这里不是精确的ns,
BOOLEAN nanosleep(LONGLONG ns) {
    /* Declarations */
    HANDLE        timer; /* Timer handle */
    LARGE_INTEGER li;    /* Time defintion */
    /* Create timer */
    if (!(timer = CreateWaitableTimer(
              NULL, TRUE, NULL)))
        return FALSE;
    /* Set timer properties */
    li.QuadPart = -ns;
    if (!SetWaitableTimer(
            timer, &li, 0, NULL, NULL, FALSE)) {
        CloseHandle(timer);
        return FALSE;
    }
    /* Start & wait for timer */
    WaitForSingleObject(timer, INFINITE);
    /* Clean resources */
    CloseHandle(timer);
    /* Slept without problems */
    return TRUE;
}

int main() {
    auto start =
        std::chrono::high_resolution_clock::now();
    // Wait for the timer.
    while (true) {
        nanosleep(100000);
        auto now = std::chrono::
            high_resolution_clock::now();
        printf(
            "Timer was out, elapsed time:%d.\n",
            std::chrono::duration_cast<
                std::chrono::milliseconds>(now -
                                           start)
                .count());
        start = now;
    }


    return 0;
}