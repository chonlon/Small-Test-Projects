#include <fcntl.h>
#include <iostream>
#include <cstring>




int main(int argc, char** argv) {
    int val;
    if(argc != 2) {
        std::cerr << "useage: a.out <descriptor>" << '\n';
        exit(-1);
    }

    if (val = ::fcntl(::atoi(argv[1]), F_GETFL); val < 0) {
        std::cerr << "fcntl error for fd:" << ::atoi(argv[1]);
        exit(-1);
    }

    switch (val & O_ACCMODE)
    {
    case O_RDONLY:
        std::cout << "read only";
        break;
    case O_WRONLY:
        std::cout << "write only";
        break;
    case O_RDWR:
        std::cout << "read write";
        break;
    default:
        std::cerr << "unkonw access mode";
    }

    if(val & O_APPEND)
        std::cout << ", append";
    if(val & O_NONBLOCK)
        std::cout << ", nonblocking";
    if(val & O_SYNC)
        std::cout << ", synchronous writes";

    putchar('\n');

    return 0;
}

// set example
void setFileFl(int fd, int flags) {
    int val;
    if (val = fcntl(fd, F_GETFL); val < 0) {
        std::cerr << "fcntl F_GETFL error";
    }

    val |= flags;  //保留原本的flags

    if (fcntl(fd, F_SETFL, val) < 0) {
        std::cerr << "fcntl F_SETFL error";
    }
}