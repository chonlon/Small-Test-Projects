#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <iostream>

int main(int argc, char** argv) {
    auto mqt = mq_open(argv[1], O_RDWR);
    struct mq_attr ma{};
    mq_getattr(mqt, &ma);

    std::cout << "flags: "<<ma.mq_flags << " maxmsg:" << ma.mq_maxmsg << " msgsize:" << ma.mq_msgsize << " curmsgs:" << ma.mq_curmsgs << '\n';
    return 0;
}