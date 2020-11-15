#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>
#include <filesystem>
#include <fstream>

int main() {
    // FOCUS ON open openat read write function.
    if(int i = open("/etc/os-release", O_RDONLY); i != -1) {
        std::cout << "open os-release successed!\n";
        char buf[1024];
        if(read(i, buf, 1024) != -1) {
            //std::cout << "read os-release successed!:\n" << buf;
            // same as upon, but cool.
            std::cout << "read os-release successed!:\n";
            write(STDOUT_FILENO, buf, strlen(buf));
        } else {
            std::cout << "read os-release failed!:\n";
        }
    } else if(i == -1) {
        std::cout << "open os-release failed!\n";
    }

    std::cout << "<=======create test.txt=======>\n";
    const char* source = "hello world";
    // create a file in current dir
    // openat use 1st para to mark dir which will use as parent dir.
    // here AT_FDCWD means current dir fd.
    int fd = openat(AT_FDCWD, "test.txt",
                    O_CREAT|
                    O_TRUNC|
                    O_RDWR,
                    S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP);
    auto temp = S_IRUSR|S_IWUSR|S_IXUSR;
    std::cout << temp << '\n';
    if(write(fd, source, strlen(source)) == -1) {
        std::cout << "write error!\n";
    } else {
        std::cout << "write success\n";
    }

    std::cout << "<=======std file functions=======>\n";
    if(std::filesystem::exists(std::filesystem::path("./test.txt"))) {
        std::cout << "check test.txt exists pass.\n";
        // istream is not easy to use.
        std::ifstream ifs("test.txt", std::ios_base::in);

#define READ_1
#ifdef READ_1
        std::stringstream ss;
        char c;
        while(ifs.get(c)) {
            ss << c;
        }
        std::string s(ss.str());
         
        if(s == source) {
            std::cout << "content got is correct.\n";
        }
#else
        char buf[1024]{0};
        ifs.read(buf, 1024);

        if(!strcmp(source, buf)) {
            std::cout << "content got is correct.\n";
        }
#endif
    }

    std::ofstream ofs(std::filesystem::path("test2.txt"), std::ios::out);
    ofs << "double hello";
    if(std::filesystem::exists(std::filesystem::path("./test2.txt"))) {
        std::cout << "check test2.txt exists pass.\n";
    }

// FOCUS ON dup dup2
    std::cout << "<======dups=========>\n";
    int fd1 = dup(STDOUT_FILENO);
    int fd2 = dup2(STDOUT_FILENO, STDERR_FILENO);
    write(fd1, "Hello ", 6);
    write(fd2, "World!\n", 7);
    write(STDERR_FILENO, "你好世界\n", 13);

    return 0;
}