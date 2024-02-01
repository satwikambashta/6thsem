# Write a UDP time server to display the current time and day.

import socket
udp_host = socket.gethostname()# Host IP
udp_port = 12345# specified port to connect

with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
    # Send a request to the server
    s.sendto(b'', (udp_host, udp_port))

    # Wait for a response from the server
    data, _ = s.recvfrom(1024)
    print(f"Received time and day of week from server: {data.decode()}")
