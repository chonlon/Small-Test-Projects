#include <fcntl.h>
#include <iostream>
#include <unistd.h>

int main() {
    int fd = -1;
    if (fd = open("/etc/os-release", O_RDONLY, S_IRUSR); fd == -1) {
        std::cerr << "open file failed\n";
    }

    // close here. 不过很多时候不需要调用这个, 因为内核在进程终止的时候关闭所有打开的文件
    // 成功返回0, 不成功返回-1
    if(close(fd) < 0) {
        std::cerr << "close file failed!\n";
    }
    return 0;
}