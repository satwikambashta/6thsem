import socket
host = socket.gethostname()
port=12345
s=socket.socket()
s.connect((host,port))

print('Welcome User!')
data=s.recv(1024)
s.close()