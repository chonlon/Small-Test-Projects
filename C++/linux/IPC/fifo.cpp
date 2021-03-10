#include "header.h"
#include <string>

int main(int argc, char* argv[]) {
    if(argc < 2) std::cout << "usage: fifo read/write\n";

const char* fifo_path_name = "/tmp/fifo.111";
constexpr mode_t fifo_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;

    int fd = -1;
    char readbuf[100];
    std::string writemsg;
    if((mkfifo(fifo_path_name, fifo_mode) < 0) && (errno != EEXIST)) {
        std::cout << "cannot create fifo: " << fifo_path_name << '\n';
    }

    std::string mode(argv[1]);
    //不用信号量很难做到时序同步. 这个例子加上sleep控制, 在一段时间以后也会出现两段死锁等待对方的现象.
    // 或者一端只做读, 一端只做写
    if(mode == "read") {
        fd = open(fifo_path_name, O_RDWR);
        writemsg = "hello server\n";
        int count = 0;
        while(true) {
            if(count == 10) {
                count = 0;
                std::cout << "recv 10 msg\n";
                write(fd, writemsg.data(), writemsg.size());
                usleep(500000);
            }
            read(fd, readbuf, 100);
            std::cout << "count " << count  << ':'<< readbuf;

            usleep(500000);
            ++count;
        }
    } else if(mode == "write") {
        sleep(5);
        fd = open(fifo_path_name, O_RDWR);
        writemsg = "hello client\n";
        int count = 0;
        while(true) {
            if(count == 10) {
                count = 0;
                read(fd, readbuf, 100);
                std::cout << readbuf;
                usleep(500000);
            }
            write(fd, writemsg.data(), writemsg.size());
            usleep(500000);
            ++count;
        }
    } else {
        std::cout << "invaild args\n";
    }

    close(fd);
    return 0;
}