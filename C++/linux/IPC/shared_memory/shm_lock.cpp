#include <cstring>
#include <fcntl.h> /* For O_* constants */
#include <iostream>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <sys/types.h>
#include <unistd.h>
//参考https://gist.github.com/yamnikov-oleg/abf61cf96b4867cbf72d

struct shared_mutex_t
{
    pthread_mutex_t* ptr;
    int shm_fd;
    std::string name;
    int created;
};

shared_mutex_t shared_mutex_init(const char* name) {
    struct shared_mutex_t mutex = {nullptr, -1, "", 0};
    errno                       = 0;

    mutex.shm_fd = shm_open(name, O_RDWR, 0660);
    if (errno == ENOENT) {
        mutex.shm_fd = shm_open(name, O_RDWR | O_CREAT, 0660);

        //分成两步来使pthread_mutexattr_init不在多个进程中调用.
        // 即首次create共享内存的进程也去初始化互斥量.
        mutex.created = 1;
    }

    if (mutex.shm_fd == -1) {
        perror("shm_open");
        return mutex;
    }
    if (ftruncate(mutex.shm_fd, sizeof(pthread_mutex_t)) != 0) {
        perror("ftruncate");
        return mutex;
    }

    pthread_mutex_t* mutex_ptr =
        static_cast<pthread_mutex_t*>(mmap(nullptr,
                                           sizeof(pthread_mutex_t),
                                           PROT_READ | PROT_WRITE,
                                           MAP_SHARED,
                                           mutex.shm_fd,
                                           0));
    if (mutex_ptr == MAP_FAILED) {
        perror("mmap");
        return mutex;
    }
    if (mutex.created) {
        pthread_mutexattr_t attr;
        if (pthread_mutexattr_init(&attr)) {
            perror("pthread_mutexattr_init");
            return mutex;
        }
        if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)) {
            perror("pthread_mutexattr_setpshared");
            return mutex;
        }
        if (pthread_mutex_init(mutex_ptr, &attr)) {
            perror("pthread_mutex_init");
            return mutex;
        }
    }
    mutex.ptr  = mutex_ptr;
    mutex.name = name;
    return mutex;
}

int shared_mutex_close(shared_mutex_t mutex) {
  if (munmap((void *)mutex.ptr, sizeof(pthread_mutex_t))) {
    perror("munmap");
    return -1;
  }
  mutex.ptr = NULL;
  if (close(mutex.shm_fd)) {
    perror("close");
    return -1;
  }
  mutex.shm_fd = 0;
  return 0;
}

int shared_mutex_destroy(shared_mutex_t mutex) {
  if ((errno = pthread_mutex_destroy(mutex.ptr))) {
    perror("pthread_mutex_destroy");
    return -1;
  }
  if (munmap((void *)mutex.ptr, sizeof(pthread_mutex_t))) {
    perror("munmap");
    return -1;
  }
  mutex.ptr = NULL;
  if (close(mutex.shm_fd)) {
    perror("close");
    return -1;
  }
  mutex.shm_fd = 0;
  if (shm_unlink(mutex.name.c_str())) {
    perror("shm_unlink");
    return -1;
  }
  return 0;
}

int main(int argc, char** argv) {
    // struct pthread_attr_t attr;
    // pthread_mutexattr_init(&attr);
    // pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    // struct pthread_mutex_t mutex;


    int fd = shm_open("shm_test", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        std::cout << std::strerror(errno);
        return -1;
    }
    ftruncate(fd, 100);
    auto ptr = mmap(nullptr, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    shared_mutex_t mutex = shared_mutex_init("shm_mutex");
    if (argc >= 2) {
        if (argv[1][0] == 'w') {
            for(int i = 0; i < 10; ++i) {
                pthread_mutex_lock(mutex.ptr);
                ++(*static_cast<int*>(ptr));
                sleep(3);
                pthread_mutex_unlock(mutex.ptr);
            }
            shared_mutex_close(mutex);
        } else if (argv[1][0] == 'r') {
            for(int i = 0; i < 10; ++i) {
                pthread_mutex_lock(mutex.ptr);
                std::cout << *static_cast<int*>(ptr) << '\n';
                pthread_mutex_unlock(mutex.ptr);
            }
            shm_unlink("shm_test");
            shared_mutex_close(mutex);
            shared_mutex_destroy(mutex);
        } else {
            std::cout << "usage: lock r/w\n";
        }
    }
}