import socket
import subprocess
import threading


def connect_to_wifi(ssid, password):
    wifi_interface = 'en0'  # Replace with your Wi-Fi interface name
    command = f"networksetup -setairportnetwork {wifi_interface} {ssid} {password}"
    subprocess.run(command, shell=True)

def handle_client(conn, addr):
    print(f"[NEW CONNECTION] {addr} connected.")
    
    while True:
        data = conn.recv(1024)
        response = "Temperature received successfully"
        temperature_reading = data.decode().strip()  # Remove leading/trailing whitespaces
        if temperature_reading:
            print(f"Temperature Reading from {addr}: {temperature_reading}")
           # response = "Temperature received successfully"
            conn.send(response.encode())

       
        conn.send(response.encode())

    conn.close()

def main():
    
    wifi_ssid = "Hana's phone"
    wifi_password = 'bngh5768'

    connect_to_wifi(wifi_ssid, wifi_password)

    PORT = 5608
    ADDR = ('192.168.201.187', PORT)
   

    print("Server is starting...")
    
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(ADDR)
    server.listen(5)
    
    print(f"Server is listening on {ADDR}")
    
    while True:  
        conn, addr = server.accept()
        threading.Thread(target=handle_client, args=(conn, addr)).start()
        print(f"[ACTIVE CONNECTIONS] {threading.active_count() - 9}")

if __name__ == "__main__":
    main()
