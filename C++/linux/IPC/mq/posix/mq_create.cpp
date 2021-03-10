#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(int argc, char** argv) {
    auto mqt = mq_open(argv[1], O_RDWR|O_CREAT, 0644, nullptr);
    mq_close(mqt);
    return 0;
}