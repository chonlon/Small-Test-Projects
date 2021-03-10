#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>

int main() {
    struct rlimit limit;
    getrlimit(RLIMIT_AS, &limit);
    std::cout << "soft limit: " << limit.rlim_cur / 1024/1024 << "Mib, max limit: " << limit.rlim_max /1024/1024 << "Mib\n";
    return 0;
}