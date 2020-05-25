import time

# 一个简单循环发送的命令
def sendC3Forever(client_socket):
    for i in range(1, 100):
        for j in range(1, 10000):
            result = "@C3," + str(j) + "#"
            try:
                client_socket.send(result.encode())
            except:
                print("连接已断开...", client_socket)
                client_socket.close()
                return
            else:
                print("sended : %s" % result)
                time.sleep(0.2)
    client_socket.close()