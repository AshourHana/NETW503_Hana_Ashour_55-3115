import socket
import threading
from threading import Thread
PORT = 5605
ADDR = ('127.0.0.1', PORT)
def threaded(conn, addr):
 print("[NEW CONNECTION] " + str(addr) + " connected.")
 while True :
     m = conn.recv(1024).decode()
     s='CLOSE SOCKET'
     if (m==s):
         conn.close()
         threading.Lock().release()
         break
     else:
         m= m.upper()
         conn.send(m.encode())
        
def main():
 print(" Server is starting...")
 server= socket.socket(socket.AF_INET,socket.SOCK_STREAM)
 server.bind(ADDR)
 server.listen(6)
 while True:
  conn, addr = server.accept()
  threading.Lock().acquire()
  K= Thread(target= threaded, args=(conn, addr))
  K.start()

 print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")
if __name__ == "__main__":
 main()

