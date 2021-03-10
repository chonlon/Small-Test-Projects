#include "header.h"
#include <string.h>

int main() {
    int master_to_worker_pipe[2], worker_to_master_pipe[2];
    pid_t child_pid;
    pipe(master_to_worker_pipe);
    pipe(worker_to_master_pipe);

    if((child_pid = fork()) == 0) {
        char buf[1024];
        close(master_to_worker_pipe[0]);
        close(worker_to_master_pipe[1]);

        strcpy(buf, "hello client");
        write(master_to_worker_pipe[1], buf, 1024);
        while(true) {
            int nread = read(worker_to_master_pipe[0], buf, 1024);
            std::cout << "pid 0 "<< "recv: "<< buf << '\n';
            strcpy(buf, "hello client");
            write(master_to_worker_pipe[1], buf, 1024);
            sleep(1);
        }
    } else {
        close(master_to_worker_pipe[1]);
        close(worker_to_master_pipe[0]);
        
        char buf[1024];
        while(true) {
            int nread = read(master_to_worker_pipe[0], buf, 1024);
            std::cout << "pid " << child_pid << " recv: "<< buf << '\n';
            strcpy(buf, "hello server");
            write(worker_to_master_pipe[1], buf, 1024);
            sleep(1);
        }
    }
}