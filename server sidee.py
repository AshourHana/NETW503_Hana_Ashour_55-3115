
import socket
import select
import sys
#initiate server socket with the TCP connection
server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
# binding the server socket with the localhost as ip and port number
port=5605
server_socket.bind(('127.0.0.1',port)) 
# make the socket listen on this port
server_socket.listen(1)
# listening forever
while True :

 client,add = server_socket.accept() 
 while True:
      m = client.recv(1024).decode()
      s='CLOSE SOCKET'
      if (m==s):
          client.close()
      else:
          m= m.upper()
          client.send(m.encode())
