#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <iostream>
#include <cstring>

int main(int argc, char** argv) {
    auto mqt = mq_open(argv[1], O_RDWR);
    
    auto len = strlen(argv[2]);
    auto ptr= static_cast<char*>(malloc(len));
    strcpy(ptr, argv[2]);
    mq_send(mqt, ptr, len, atoi(argv[3]));

    return 0;
}