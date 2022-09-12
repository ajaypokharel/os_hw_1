import socket


def server_program():
    # get the hostname
    host = socket.gethostname()
    port = 6013  # initiate port no above 1024

    server_socket = socket.socket()  # get instance

    server_socket.bind((host, port))  # bind host address and port together

    # configure how many client the server can listen simultaneously
    server_socket.listen(1)
    conn, _ = server_socket.accept()  # accept new connection

    while True:
        # receive data stream. it won't accept data packet greater than 1024 bytes
        data = conn.recv(2048).decode()
        print(data)

        input_data = input()
        if input_data == "FINISH": break
        conn.send(input_data.encode())  # send data to the client
        input_data = input()

    conn.close()  # close the connection


if __name__ == '__main__':
    server_program()