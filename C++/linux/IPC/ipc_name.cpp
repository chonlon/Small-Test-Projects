#include "header.h"

int main() {
    std::cout << "ipc private:" << IPC_PRIVATE << '\n';
    //std::cout << getenv("PX_IPC_NAME") << '\n';

    struct stat stat;
    int fd = open("/us/bin/ls", O_RDONLY);
    fstat(fd, &stat);

    std::cout << "st_dev:" << stat.st_dev << " st_ino:" << stat.st_ino
              << "\nsystem v ipc key:" << ftok("/usr/bin/ls", 10) << '\n';
    return 0;
}