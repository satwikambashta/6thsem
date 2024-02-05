# Write a TCP/UDP peer to peer chat system between two different machines.

import socket
serv = ('172.16.59.52', 9991)
HOST, PORT = serv[0], serv[1]
s = socket.socket()
s.bind(serv)
s.listen()
print("waiting for incoming connections\n")
conn, addr = s.accept()
print("received connection from ", addr[0], "(", addr[1], ")\n")
s_name = conn.recv(1024).decode()
print(s_name, "has connected to the chat room")
print("enter 'bye' to exit chat room\n")
name = input(str("enter your name: "))
conn.send(name.encode())
while True:
    msg = conn.recv(1024).decode()
    if(msg=='bye'):
        conn.close()
        break
    print(s_name, ":", msg)
    msg = input(str("me: "))
    if msg == "bye":
        conn.send(msg.encode())
        print("\n")
        conn.close()
        break
    conn.send(msg.encode())
