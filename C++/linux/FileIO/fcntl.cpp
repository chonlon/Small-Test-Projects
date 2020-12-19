#include <fcntl.h>
#include <iostream>
#include <cstring>

#include <memory>


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

// file lock example
class FileLocker {
public:
static bool RdLock(int fd) {
    return setInner(fd, F_RDLCK);
}

static bool WrLock(int fd) {
    return setInner(fd, F_WRLCK);
}

static bool UnLock(int fd) {
    return setInner(fd, F_UNLCK);
}

static std::unique_ptr<::flock> GetFileLock(int fd) {
    auto _flock = std::make_unique<::flock>();

    if((fcntl(fd, F_GETLK, _flock.get())) < 0) {
        return nullptr;
    }
    return _flock;
}

private:

static bool setInner(int fd, decltype(::flock::l_type) type) {
    struct flock _flock;
    _flock.l_type = type;
    _flock.l_whence = SEEK_SET;
    _flock.l_len  = 0;
    
    if ((fcntl(fd, F_SETLK, &_flock)) < 0) {
        return false;
    }
    return true;
}

};