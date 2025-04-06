import socket


port = input("what port to use?")
if int(port) > 65535 or int(port) < 1024:
    print("cant use this port")

try:
    client =socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    client.connect(('127.0.0.1' , int(port)))
    client.send('Hello'.encode())
except socket.error:
    print("An Error occured!")


print(client.recv(1024))