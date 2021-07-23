#include <thread>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif
int main() {
    std::cout << "hello cmake!\n";
    std::thread t([](){
        std::cout << "hello cmake!\n" << getpid() << ' ' << gettid() << ' ' << pthread_self() << ' ' << std::this_thread::get_id() << '\n';
    });
    t.join();
    return 0;
}