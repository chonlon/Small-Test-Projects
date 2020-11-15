#pragma once
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdint.h>

namespace sylar {
    pid_t GetThreadId();
    uint32_t GetFiberId();
}
