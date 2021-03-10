#include <sys/msg.h>
#include <iostream>
#include <fcntl.h>

int main() {
    auto mqd = msgget(IPC_PRIVATE, IPC_CREAT|0640);
    const char* msg = "hello recv";
    msgsnd(mqd, msg, sizeof(msg), 0);
    char buff[1024];
    msgrcv(mqd, buff, 1024, 0, MSG_NOERROR);
    std::cout << "recv: "<< buff << '\n';

    msgctl(mqd, IPC_RMID, nullptr);
}