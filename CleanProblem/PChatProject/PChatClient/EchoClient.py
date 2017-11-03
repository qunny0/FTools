import socket


HOST = "127.0.0.1"

PORT = 3333

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

while True:
    cmd = raw_input("Please input message : ")

    print("begin send: " + cmd)
    s.send(cmd)
    print("end send: " + cmd)

    data = s.recv(1024)

    print(data)
