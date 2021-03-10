#include <fcntl.h> /* For O_* constants */
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int main(int argc, char** argv) {
    
    int fd = shm_open("shm_test", O_RDWR | O_CREAT, 0644);
    if(fd == -1) {
        std::cout << std::strerror(errno);
        return -1;
    }
    ftruncate(fd, 100);
    auto ptr = mmap(nullptr, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(argc >= 2) {
        if(argv[1][0] == 'w') {
            strcpy(static_cast<char*>(ptr), "hello shm\n");
        } else if(argv[1][0] == 'r'){
            write(1, ptr, 100);
            shm_unlink("shm_test");
        } else {
            std::cout << "usage: base r/w\n";
        }
    }
    
}