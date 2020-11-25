#pragma once

#include "log.h"
#include "util.h"
#include <assert.h>
#include <string.h>



#define SYLAR_ASSERT(x)                                \
    if (!(x)) {                                        \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())              \
            << "ASSERTION: " << #x << "\nbacktrace:\n" \
            << sylar::BacktraceToString(10, 2, "\t");  \
        assert(x);                                     \
    }

#define SYLAR_ASSERT2(x, w)                           \
    if (!(x)) {                                       \
        SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())             \
            << "ASSERTION: " << #x << '\n'            \
            << w << "\nbacktrace:\n"                  \
            << sylar::BacktraceToString(10, 2, "\t"); \
        assert(x);                                    \
    }