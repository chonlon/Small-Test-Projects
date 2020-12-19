//#include <cstdio>
#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <thread>

void foo(int signum) {
    printf("hello from invoke func");
    // std::cout << "hello from invoke func\n";
}

::itimerval oldit;
int main() {
    ::itimerval it;
    ::signal(SIGALRM, [](int signum) {
        // std::printf("hello from invoke func");
        std::cout << "hello from invoke func\n";
        //std::cout << "sec: " << oldit.it_interval.tv_sec << '\n';
    });
    //::signal(SIGALRM, foo);

    it.it_value.tv_sec     = 5;
    it.it_value.tv_usec    = 0;
    it.it_interval.tv_sec  = 3;
    it.it_interval.tv_usec = 0;
    if (::setitimer(ITIMER_REAL, &it, &oldit)) {
        perror("error");
        return -1;
    }

    while (1) {
        std::this_thread::yield();
    }

    return 0;
}