#include <cstring>
#include <iostream>

#include <fcntl.h>
#include <unistd.h>

// write 返回值: 成功返回成功写入的字节数, 出错返回-1

int main() {
    int fd = -1;
    if (fd = ::open("./files/write.txt", O_WRONLY | O_CREAT); fd < 0) {
        std::cerr << "open file failed\n";
    }

    const char* str = "hello from write.cpp";

    if (int byte_written = ::write(fd, str, ::strlen(str)); byte_written >= 0) {
        std::cout << byte_written << '\n';
    } else {
        std::cerr << "wirte file failed" << '\n';
    }

    return 0;
}