// pthread的基本使用
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int x = 0;

void *mythread(void *arg) {
    x = 1;
    printf("Child process set x=1\n");
    return NULL;
}

int main(int argc, char* argv[]) {
    pthread_t tid;
    void *vp;
    if(pthread_create(&tid, NULL, mythread, NULL) != 0) {
        perror("thread_create");
        exit(-1);
    }

    if(pthread_join(tid, nullptr) != 0) {
        perror("pthread_join");
        exit(-1);
    }
    printf("parent process sees x = %d\n", x);
    return 0;
}