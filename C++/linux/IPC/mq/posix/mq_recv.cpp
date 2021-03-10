#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <iostream>
#include <cstring>

int main(int argc, char** argv) {
    auto mqt = mq_open(argv[1], O_RDWR);
    
    auto len = strlen(argv[1]);
    char buf[8192]{0};
    unsigned int proi = atoi(argv[2]);
    // 需要注意的是create的时候没有指定attr的msgsize, 所以这里的len(8192)可能是错误的
    if((mq_receive(mqt, buf, 8192, &proi)) == -1)
        std::cout << "recv mq failed" << std::strerror(errno) << '\n';
    std::cout << "recv: " << buf << '\n';

    return 0;
}