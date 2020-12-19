#include <signal.h>
#include <iostream>
#include <unistd.h>


int main() {
    ::sigset_t sig_set;
    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGINT);
    sigprocmask(SIG_BLOCK, &sig_set, nullptr);

    sleep(5);

    //sigdelset(&sig_set, SIGINT);
    sigprocmask(SIG_UNBLOCK, &sig_set, nullptr);
    sleep(100);
    return 0;
}