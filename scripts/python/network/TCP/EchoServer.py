import socket
import selectors
import time


def recv_data(conn):
    data = conn.recv(1024)
    if data:
        print(data.decode())
    else:
        e_poll.unregister(conn)
        conn.close()


def acc_conn(p_server):
    conn, addr = p_server.accept()
    print("[*] Acception connection from %s:%d" % (addr[0], addr[1]))
    e_poll.register(conn, selectors.EVENT_READ, recv_data)


if __name__ == "__main__":
    CONN_ADDR = ("127.0.0.1", 2006)
    server = socket.socket()
    server.bind(CONN_ADDR)
    server.listen(6)
    e_poll = selectors.DefaultSelector()
    e_poll.register(server, selectors.EVENT_READ, acc_conn)
    print("port: 2006 wating for connect...")
    while True:
        # 事件循环不断地调用select获取被激活的socket
        events = e_poll.select()
        # print(events)
        for key, mask in events:
            call_back = key.data
            # print(key.data)
            call_back(key.fileobj)
