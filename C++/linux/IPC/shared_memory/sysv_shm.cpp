#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h> 
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {

    auto key = ftok("/tmp/shm_test", 0);
    int id = shmget(key, 100, IPC_CREAT | 0644);
    if (id == -1) {
        std::cout << std::strerror(errno);
        return -1;
    }
    //第三个参数在第二个参数指定地址后有效.
    auto ptr = shmat(id, nullptr, 0);

    if (argc >= 2) {
        if (argv[1][0] == 'w') {
            strcpy(static_cast<char*>(ptr), "hello shm\n");
        } else if (argv[1][0] == 'r') {
            write(1, ptr, 100);
            shmctl(id, IPC_RMID, nullptr);
        } else {
            std::cout << "usage: base r/w\n";
        }
    }
}