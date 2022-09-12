import socket


def client_program():
    host = socket.gethostname()  # as both code is running on same pc
    port = 6013  # socket server port number

    client_socket = socket.socket()  # instantiate
    client_socket.connect((host, port))  # connect to the server

    while True:
        input_data = input()
        if input_data == "FINISH": break

        client_socket.send(input_data.encode())  # send input_data

        data = client_socket.recv(2048).decode()  # receive response

        print(data)  # show in terminal

    client_socket.close()  # close the connection


if __name__ == '__main__':
    client_program()