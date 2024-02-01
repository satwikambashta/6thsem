# Write a UDP simple chat program for message send and receive.


import socket
udp_host = socket.gethostname()# Host IP
udp_port = 12345# specified port to connect

# Create a UDP socket
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    s.bind((udp_host, udp_port))
    print("###SERVER IS LISTENING###")

    while True:
        # Receive a request
        data, addr = s.recvfrom(1024)
        print(f"Received request from {addr}")
        data1, _ = s.recvfrom(1024)
        print(f"Server received:{data1}")
        now=input("Enter some text to send:")
        s.sendto(now.encode(), addr)
        print(f"Server Sent: {now}")


        # Send the current date and time back to the client
        # s.sendto(now.encode(), addr)