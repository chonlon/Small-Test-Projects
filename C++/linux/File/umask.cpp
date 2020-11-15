#include <fcntl.h>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>

constexpr int RWRWRW =
    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

int main() {
    ::umask(0);

    if(creat("foo", RWRWRW) < 0) {
        std::cerr << "creat error for foo\n";
    }

    ::umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if(creat("bar", RWRWRW) < 0) {
        std::cerr << "creat error for bar\n";
    }
    return 0;
}