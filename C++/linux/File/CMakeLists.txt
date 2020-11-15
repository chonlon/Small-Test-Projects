set(IO_FILE
    FileStat.cpp
    FileType.cpp
    FileAccess.cpp
    umask.cpp
    fmemopen.cpp
)

AddExeFromFiles("File" ${IO_FILE})