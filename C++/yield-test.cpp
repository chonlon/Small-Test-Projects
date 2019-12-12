#include <iostream>
#include <chrono>
#include <thread>
#define kpasufunc 5

inline void asm_volatile_pause() {
#if kpasufunc == 1
  ::_mm_pause();
#elif kpasufunc == 2
  asm volatile("pause");
#elif kpasufunc == 3
  asm volatile("yield");
#elif kpasufunc == 4
  asm volatile("or 27,27,27");
#elif kpasufunc == 5
  std::this_thread::yield();
#endif

}

// 建议其他线程运行一小段时间的“忙睡眠”
void little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    auto kCount = 10000;
    auto i = 0;
    do {
        if(++i < kCount)
            asm_volatile_pause();
        else
            std::this_thread::yield();
        std::cout << (std::chrono::high_resolution_clock::now() - start).count() << "\n";
        //std::this_thread::yield();    
    } while (std::chrono::high_resolution_clock::now() < end);
    std::cout << "pause time: " << i << "\n";
}
 
int main()
{
    auto start = std::chrono::high_resolution_clock::now();
 
    little_sleep(std::chrono::microseconds(10));
 
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for "
              << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
              << " microseconds\n";
}