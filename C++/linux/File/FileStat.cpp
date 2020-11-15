#include <cstring>
#include <iostream>
#include <sys/stat.h>

int timespec2str(char* buf, uint len, struct timespec* ts) {
    int ret;
    struct tm t;

    tzset();
    if (localtime_r(&(ts->tv_sec), &t) == NULL)
        return 1;

    ret = strftime(buf, len, "%F %T", &t);
    if (ret == 0)
        return 2;
    len -= ret - 1;

    ret = snprintf(&buf[strlen(buf)], len, ".%09ld", ts->tv_nsec);
    if (ret >= len)
        return 3;

    return 0;
}

int main() {
    struct stat file_stat;
    if (::stat("/etc/os-release", &file_stat) < 0) {
        std::cerr << "get file stat failed\n";
        exit(-1);
    }

    char buf[60];

    // strftime(buf, sizeof(buf), "%Y-%m-%d, %H:%M:%S",
    // localtime_r(&file_stat.st_atim.tv_sec));
    timespec2str(buf, sizeof(buf), &file_stat.st_atim);
    std::cout << "access time: " << buf << '\n';
    timespec2str(buf, sizeof(buf), &file_stat.st_ctim);
    std::cout << "create time: " << buf << '\n';

    std::cout << "file size:" << file_stat.st_size << '\n'
              << "best io block size:" << file_stat.st_blksize << '\n'
              << "number of block:" << file_stat.st_blocks << '\n'
              << "device number:" << file_stat.st_dev << '\n'
              << "group id:" << file_stat.st_gid << '\n'
              << "i-node number:" << file_stat.st_ino << '\n'
              << "file type & mode:" << file_stat.st_mode << '\n';

    return 0;
}