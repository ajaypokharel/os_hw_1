import socket


def server_program():
    # get the hostname
    clients = []
    host = socket.gethostname()
    port = 5678  # initiate port no above 1024

    server_socket = socket.socket()  # get instance

    server_socket.bind((host, port))  # bind host address and port together

    # configure how many client the server can listen simultaneously
    server_socket.listen(5)
    print("Listening at port 5678...")

    conn, addr = server_socket.accept()  # accept new connection

   

    while True:
        # check if the client is new
        # conn, addr = server_socket.accept()
        if not addr in clients:
            clients.append(addr)
            hello_msg = "Hello"
            conn.send(hello_msg.encode())

        data = conn.recv(8192).decode()
        print(data)

        input_data = input()

        conn.sendall(input_data.encode())  # send data to the client

    conn.close()  # close the connection


if __name__ == '__main__':
    server_program()