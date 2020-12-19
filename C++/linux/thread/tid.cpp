#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>

#include <iostream>

int main() {
    pthread_t tid0;
    
    if((::pthread_create(&tid0, nullptr, [](void* arg)->void*{
        std::cout << "self: " << ::pthread_self() << '\n'
         << "gettid: " << ::gettid() << '\n'
         << "syscall get tid: " << ::syscall(SYS_gettid) << '\n';
        return nullptr;
    }, nullptr)) != 0) {
        std::cerr <<"error on pthread create\n";
    };

    std::cout << "pthread_t:" << tid0 << '\n';

    ::pthread_join(tid0, nullptr);

    return 0;
}