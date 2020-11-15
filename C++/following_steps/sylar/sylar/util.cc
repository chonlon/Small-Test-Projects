#include "util.h"


namespace sylar {

pid_t GetThreadId() {
    return static_cast<int>(::syscall(SYS_gettid));
}

uint32_t GetFiberId() {
    return 0;
}
}
