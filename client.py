import socket

host = "localhost"
port = 7777
launched = True

try:
	clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	connection = clientSocket.connect((host, port))
	print("Client connécté")
	while launched:
		user_text = input(">>>")
		clientSocket.send(user_text.encode("utf8"))
		if user_text == "quit":
			launched = False
except ConnectionRefusedError:
	print("Pas Arriver a se connecter :/")
finally:
	clientSocket.close()