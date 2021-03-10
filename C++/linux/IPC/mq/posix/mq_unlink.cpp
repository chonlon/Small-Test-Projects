#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(int argc, char** argv) {
    mq_unlink(argv[1]);
    return 0;
}