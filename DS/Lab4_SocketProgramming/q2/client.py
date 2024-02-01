# Write a UDP simple chat program for message send and receive.

import socket
udp_host = socket.gethostname()# Host IP
udp_port = 12345# specified port to connect
addr = (udp_host, udp_port)

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    # Send a request to the server
    s.sendto(b'', addr)

    # Wait for a response from the server
    # data, _ = s.recvfrom(1024)
    now=input("Enter some text to send:")
    s.sendto(now.encode(), addr)
    print(f"Client Sent: {now}")
    data, _ = s.recvfrom(1024)
    print(f"Client Received: {data}")
