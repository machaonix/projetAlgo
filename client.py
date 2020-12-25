import socket

host = "localhost"
port = 7777
launched = True

try:
	clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	clientSocket.connect((host, port))
	print("Client connécté")
	pseudo = input("Entrez un psudonyme\n>>>")
	clientSocket.send(pseudo.encode("utf8"))
	while launched:
		user_text = input(">>>")
		clientSocket.send(user_text.encode("utf8"))
		user_text = clientSocket.recv(4096)
		print(user_text.decode("utf8"))
		if user_text == "quit":
			launched = False
except ConnectionRefusedError:
	print("Pas Arriver a se connecter :/")
finally:
	clientSocket.close()