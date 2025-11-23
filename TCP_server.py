import socket 
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
server_socket.bind(('localhost', 8080)) 
server_socket.listen(1) 
print("Server is listening on port 8080 ... ") 
conn, addr = server_socket.accept() 
print("Connected by:", addr) 
filename = conn.recv(1024).decode() 
try: 
    with open(filename, 'r') as f: 
        data = f.read() 
    conn.send(data.encode()) 
except FileNotFoundError: 
    conn.send(b"File not found on server.")
conn.close() 
server_socket.close() 
