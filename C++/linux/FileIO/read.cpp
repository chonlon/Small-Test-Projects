#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string_view>

// read 返回值: 成功返回读到的字节数, 如果已到文件尾返回0, 出错返回-1

void readWithSmallBuf() {
    int fd = -1;
    if (fd = open("/etc/os-release", O_RDONLY); fd < 0) {
        std::cerr << "open file failed\n";
    }

    constexpr int bufsize = 20; // 不过很少会使用这么小的缓冲区, read自己就是系统调用, 这里只是举个例子
    char buf[bufsize];
    int i = 0;
    do {
        i = ::read(fd, buf, bufsize);
        std::cout << std::string_view(buf, i); // 使用string_view主要是方便告诉cout buf的size
    } while (i == bufsize);
    std::cout << std::endl;

    ::close(fd);
}

int main() {
    int fd = -1;
    if (fd = ::open("/etc/os-release", O_RDONLY); fd < 0) {
        std::cerr << "open file failed\n";
    }

    char buf[400];
    std::cout << ::read(fd, buf, sizeof(buf)) << '\n';
    // return 0 here
    std::cout << "call with file which offset attch end of file returned: "<< ::read(fd, buf, sizeof(buf)) << '\n';
    // 并且buf在第二次调用中没有被改变
    std::cout << buf << '\n';
    ::close(fd);

    // 所以不是必须准备足够大的缓冲区:
    readWithSmallBuf();

    return 0;
}