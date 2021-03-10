set(RLimit_FILES
    memory.cpp
)

AddExeFromFilesWithLib("" "rlimit" ${RLimit_FILES})