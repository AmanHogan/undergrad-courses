import socket
import threading

HEADER = 64
FORMAT = 'utf-8'
DISCONNECT = "!DISCONNECT"
# PORT in which data will be received and sent
PORT = 5050

# Gets the IPv4 Address of Device by using the device name
SERVER_IP = socket.gethostbyname(socket.gethostname())

# Return a socket of type: [IPV4] ---------- [TCP]
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Create a tuple for address
ADDRESS = (SERVER_IP, PORT)

# Bind socket to IP and Port
server_socket.bind(ADDRESS)


def handle_client(conn, addr):
    print(f"NEE CONNECTION {addr} connected.")

    connected = True
    while connected:
        msg_length = conn.recv(HEADER).decode(FORMAT)

        if msg_length:
            msg_length = int(msg_length)
            msg = conn.recv(msg_length).decode(FORMAT)
            print(f"{addr} : {msg}")

            if msg == DISCONNECT:
                connected = False
    conn.close()


def start():
    server_socket.listen()
    print(f"Listing on {SERVER_IP}")
    while True:
        conn, addr = server_socket.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()
        print(f"[ACTIVE CONNECTIONS] {threading.activeCount() - 1}")


print("Server is starting....")
start()
