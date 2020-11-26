#include "util.h"
#include "log.h"
#include "fiber.h"
#include <execinfo.h>

namespace sylar {

sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

pid_t GetThreadId() {
    return static_cast<int>(::syscall(SYS_gettid));
}

uint64_t GetFiberId() {
    return sylar::Fiber::GetFiberId();
}

void Backtrace(std::vector<std::string>& bt, int size, int skip) {
    void** array   = static_cast<void**>(malloc(sizeof(void*) * size));
    int s       = ::backtrace(array, size);
    char** strings = backtrace_symbols(array, s);
    if (strings == nullptr) {
        SYLAR_LOG_ERROR(g_logger) << "backtrace_symbols error";
        return;
    }
    for(int i = skip; i < s; ++i) {
        bt.push_back(strings[i]);
    }
    free(strings);
    free(array);
}

std::string BacktraceToString(int size, int skip, const std::string& prefix) {
    std::vector<std::string> bt;
    Backtrace(bt, size, skip);
    std::stringstream ss;
    for(size_t i = 0; i < bt.size(); ++i) {
        ss << prefix << bt[i] << '\n';
    }
    return ss.str();
}
}  // namespace sylar
