import socket

host, port = ('', 7777)

socketServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socketServer.bind((host, port))

print("Server démarré...")

while True:
	print("En Écoute")
	socketServer.listen(5)
	connection, addresse = socketServer.accept()
	data = connection.recv(4096)
	print(data.decode("utf8"))

connection.close()
socketServer.close()
