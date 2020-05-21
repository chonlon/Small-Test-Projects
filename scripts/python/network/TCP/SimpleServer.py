import os
import sys

dir_mytest = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.append(dir_mytest)

import network.TCP.ListenFuncs

import socket
import threading
import time

bind_ip = "0.0.0.0"  # 监听所有可用的接口
bind_port = 2006  # 非特权端口号都可以使用

# AF_INET：使用标准的IPv4地址或主机名，SOCK_STREAM：说明这是一个TCP服务器
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 服务器监听的ip和端口号
server.bind((bind_ip, bind_port))

print("[*] Listening on %s:%d" % (bind_ip, bind_port))

# 最大连接数
server.listen(5)


while True:
    # 等待客户连接，连接成功后，将socket对象保存到client，将细节数据等保存到addr
    client, addr = server.accept()

    print("[*] Acception connection from %s:%d" % (addr[0], addr[1]))

    client_handler = threading.Thread(target=network.TCP.sendC3Forever, args=(client,))
    client_handler.start()
