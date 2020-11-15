#include <fcntl.h>
#include <iostream>

// dir includes
#include <dirent.h>
#include <sys/types.h>

// open 以及 openat函数成功返回文件描述符, 失败返回-1
// 返回的文件描述符是进程可用的最小文件描述符

int main() {

    int fd = -1;
    if (fd = open("/etc/os-release", O_RDONLY, S_IRUSR); fd == -1) {
        std::cerr << "open file failed\n";
    }

    auto dir  = opendir("./files");
    int dirfd = ::dirfd(dir);

    if (fd = openat(dirfd, "openat", O_WRONLY | O_CREAT | O_TRUNC); fd == -1) {
        std::cerr << "open at failed\n";
    }
}