#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
#define err_sys printf


int main() {
    int fd;

    if ((fd = creat("./files/file.hole", S_IRUSR|S_IWUSR)) < 0) {
        err_sys("creat error\n");
    }

    if (write(fd, buf1, 10) != 10)
        err_sys("buf1 write error\n");

    if (lseek(fd, 16384, SEEK_SET) == -1) {
        err_sys("lseek error\n");
    }

    if (write(fd, buf2, 10) != 10) {
        err_sys("buf2 write error\n");
    }
    return 0;
}