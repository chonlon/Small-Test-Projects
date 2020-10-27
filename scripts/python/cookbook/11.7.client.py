import hmac
import os
from socket import socket, AF_INET, SOCK_STREAM


def client_authenticate(connection, secret_key):
    message = connection.recv(32)
    hash = hmac.new(secret_key, message)
    digest = hash.digest()
    connection.send(digest)

secret_key = b'peekaboo'#可以修改这里看看
s = socket(AF_INET, SOCK_STREAM)
s.connect(('121.196.19.12', 22000))
client_authenticate(s, secret_key)
s.send(b'Hello world!')
resp = s.recv(1024)
print(resp.decode('utf-8'))
