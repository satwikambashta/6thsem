# Write a UDP time server to display the current time and day.

import socket
import time
udp_host = socket.gethostname()# Host IP
udp_port = 12345# specified port to connect

# Create a UDP socket
with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    s.bind((udp_host, udp_port))
    print(f"UDP server listening on {udp_host}:{udp_port}")

    while True:
        # Receive a request
        data, addr = s.recvfrom(1024)
        print(f"Received request from {addr}")

        # Get the current date and time
        now = time.ctime(time.time()) + "\r\n"

        # Send the current date and time back to the client
        s.sendto(now.encode(), addr)
