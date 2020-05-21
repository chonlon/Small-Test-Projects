import os
import sys

current_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.append(current_dir)
print(current_dir)

import socket
import selectors
import threading

import TCP.ListenFuncs


# 注册一个epllo事件
# 1. socket
# 2.事件可读
# 3.回调函数 把一个函数当成变量传到函数里


def recv_data(conn):
    data = conn.recv(1024)

    if data:
        print("recv: %s" % data.decode())
    else:
        e_poll.unregister(conn)
        conn.close()


def acc_conn(p_server):
    conn, addr = p_server.accept()
    print("Connected by", addr)

    print("[*] Acception connection from %s:%d" % (addr[0], addr[1]))
    e_poll.register(conn, selectors.EVENT_READ, recv_data)
    client_handler = threading.Thread(
        target=TCP.ListenFuncs.sendC3Forever, args=(conn,)
    )
    client_handler.start()


if __name__ == "__main__":
    CONN_ADDR = ("127.0.0.1", 9999)
    server = socket.socket()
    server.bind(CONN_ADDR)
    server.listen(6)  # 表示一个客户端最大的连接数

    # 生成一个epllo选择器实例 I/O多路复用，监控多个socket连接
    # e_poll = selectors.EpollSelector()  # window没有epoll使用selectors.DefaultSelector()实现多路复用
    e_poll = selectors.DefaultSelector()
    e_poll.register(server, selectors.EVENT_READ, acc_conn)

    print("port: 9999 wating for connect...")

    # 事件循环
    while True:
        # 事件循环不断地调用select获取被激活的socket
        events = e_poll.select()
        # print(events)
        """[(SelectorKey(fileobj= < socket.socket
        laddr = ('127.0.0.1',9999) >,……data = < function acc_conn at 0xb71b96ec >), 1)]
        """
        for key, mask in events:
            call_back = key.data
            # print(key.data)
            call_back(key.fileobj)
