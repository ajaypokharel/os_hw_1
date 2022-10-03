import socket


def client_program():
    host = socket.gethostname()  # as both code is running on same pc
    port = 5678  # socket server port number

    client_socket = socket.socket()  # instantiate
    client_socket.connect((host, port))  # connect to the server

    data = client_socket.recv(8192).decode()
    print(data)
    
    while True:
        input_data = input()

        client_socket.send(input_data.encode())  # send input_data

        data = client_socket.recv(8192).decode()  # receive response
        if data == "EXIT": break

        print("S:"+data)  # show in terminal

    client_socket.close()  # close the connection


if __name__ == '__main__':
    client_program()