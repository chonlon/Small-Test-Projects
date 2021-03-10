set(IPC_FILES
    ipc_name.cpp
    systemv_ipc_key.cpp
    pipe.cpp
    popen.cpp
    fifo.cpp
    #mq/posix_mqcreate.cpp
    #mq/posixmq.cpp
    mq/posix/mq_create.cpp
    mq/posix/mq_unlink.cpp
    mq/posix/mq_send.cpp
    mq/posix/mq_recv.cpp
    mq/posix/mq_attr.cpp
    mq/systemv/mq_in_all.cpp
    shared_memory/shm_base.cpp
    shared_memory/sysv_shm.cpp
    #shared_memory/shm_lock.cpp
)

AddExeFromFilesWithLib("rt" "IPC" ${IPC_FILES})