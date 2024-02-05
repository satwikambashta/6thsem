# Try to debug the error in the code and execute it.

import socket
serverIP = 'localhost'
serverPort = 16000
clientSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
clientSock.connect((serverIP, serverPort))

message = input("Input integers with space in between: ").encode()
# clientSock.connect((serverIP, serverPort))
# message = raw_input("Input integers with space in between: ")
#message2 = input("Enter the length of the set: ").encode()

clientSock.send(message)
#clientSock.send(message2)

#data = clientSock.recv(1024)
data = clientSock.recv(1024).decode()

temp = [float(x) for x in data.split(' ')]

print("The total of all numbers is: " + str(temp[0]))
print("The lowest number is: " + str(temp[1]))
print("The highest number is: " + str(temp[2]))
print("The mean is: " + str(temp[3]))

clientSock.close()

# import socket
# serverIP = 'localhost'
# serverPort = 16000
# clientSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# clientSock.connect((serverIP, serverPort))
# message = raw_input("Input integers with space in between: ")
# message2 = raw_input("Enter the length of the set: ")
# clientSock.send(message)
# clientSock.send(message2)
# data = clientSock.recv(1024)
# temp = [float(x) for x in data.split(' ')]
# print("The total of all numbers is: " + str(temp[0]))
# print("The lowest number is: " + str(temp[1]))
# print("The highest number is: " + str(temp[2]))
# print("The mean is: " + str(temp[3]))
# clientSock.close()
