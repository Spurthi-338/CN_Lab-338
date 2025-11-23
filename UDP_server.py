import socket

server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_socket.bind(('localhost', 8081))
print("UDP Server is ready ... ")

filename, addr = server_socket.recvfrom(1024)
filename = filename.decode()
print(f"Requested file: {filename}")

try:
    with open(filename, 'r') as f:
        data = f.read()
    server_socket.sendto(data.encode(), addr)
except FileNotFoundError:
    server_socket.sendto(b"File not found on server.", addr)

server_socket.close()
