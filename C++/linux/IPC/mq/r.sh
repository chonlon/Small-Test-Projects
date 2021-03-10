./IPC_mq_create /t.1
./IPC_mq_attr /t.1
./IPC_mq_send /t.1 'hello recv' 6
./IPC_mq_attr /t.1
./IPC_mq_recv /t.1 6