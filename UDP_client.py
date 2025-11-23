import socket

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ('localhost', 8081)
filename = input("Enter filename to request: ")

client_socket.sendto(filename.encode(), server_address)

data,_ = client_socket.recvfrom(4096)
print("\n --- File Content --- \n")
print(data.decode())

client_socket.close()
