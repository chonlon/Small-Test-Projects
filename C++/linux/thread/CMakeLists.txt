set(THREAD_FILES
    pthread1.cpp
    tid.cpp
    attr.cpp
    cond.cpp
    sem.cpp
)

AddExeFromFilesWithLib("pthread" "Thread" ${THREAD_FILES})