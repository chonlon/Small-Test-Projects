#include "sylar.h"
#include "util.h"
#include <assert.h>

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_assert() {
    //SYLAR_LOG_INFO(g_logger) << '\n' << sylar::BacktraceToString(10, 2, "\t");
    //SYLAR_ASSERT(false); 
    SYLAR_ASSERT2(1==0, "abcdef xx");
}

int main(int argc, char** argv) {

    test_assert();
    //assert(false);

    return 0;
}