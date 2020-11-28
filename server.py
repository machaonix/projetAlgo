import socket

host, port = ('', 7777)

socketServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socketServer.bind((host, port))

print("Server démarré...")

while True:
    print("En Écoute")
    socketServer.listen(5)
    connection, addresse = socketServer.accept()
    while True:
        user_text = connection.recv(8192)
        connection.send(user_text)
        print(user_text.decode("utf8"))

connection.close()
socketServer.close()