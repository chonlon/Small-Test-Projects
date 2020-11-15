#include <iostream>
#include <sys/stat.h>
#include <string_view>

int main(int argc, char** argv) {
    int i;
    struct stat buf;
    std::string_view str;

    for (int i = 1; i < argc; ++i) {
        std::cout << argv[i] << '\n';
        if(lstat(argv[i], &buf) < 0) {
            std::cerr << "lstat error";
            continue;
        }

        if (S_ISREG(buf.st_mode))
            str = "regular";
        else if (S_ISCHR(buf.st_mode))
            str = "character special";
        else if (S_ISDIR(buf.st_mode))
            str = "directory";
        else if (S_ISBLK(buf.st_mode))
            str = "block special";
        else if (S_ISFIFO(buf.st_mode))
            str = "fifo";
        else if (S_ISLNK(buf.st_mode))
            str = "symblock link";
        else if (S_ISSOCK(buf.st_mode))
            str = "socket";
        else
            str = "unknown mode";
        std::cout<< str << '\n';
    }

        return 0;
}