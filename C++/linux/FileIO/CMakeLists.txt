set(IO_FILES
    open_at.cpp
    close.cpp
    lseek1.cpp
    lseek2.cpp
    read.cpp
    write.cpp
    fcntl.cpp
    FileFunctions.cpp
)

AddExeFromFiles("F_IO" ${IO_FILES})