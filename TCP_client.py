import socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
client_socket.connect(('localhost', 8080)) 
filename = input("Enter filename to request: ") 
client_socket.send(filename.encode()) 
data = client_socket.recv(4096).decode() 
print("\n --- File Content --- \n") 
print(data) 
client_socket.close()
