#pragma once
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdint.h>
#include <string>
#include <vector>


namespace sylar {
    pid_t GetThreadId();
    uint64_t GetFiberId();

    void Backtrace(std::vector<std::string>& bt, int size, int skip = 1);

    std::string BacktraceToString(int size, int skip = 2, const std::string& prefix = "");
}
