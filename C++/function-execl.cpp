#include <unistd.h>
#include <sys/types.h>
#include <thread>
#include <stdlib.h>
#include <signal.h>

pid_t running_process_id{0};

int main() {
    running_process_id = fork();
    // 在子进程中运行command, 并记录pid, 准备在下面kill之.
    if(running_process_id == 0) {
        execl("/usr/bin/python3.6", "python3", "1.py", NULL);
        exit(1);
    }

    for(int i = 0; i <10000; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    kill(running_process_id, 15);
}