import socket
import threading

class Thread_for_client(threading.Thread):
	def __init__(self, connection):
		threading.Thread.__init__(self)
		self.connection = connection

	def run(self):
		while True:
			user_text = connection.recv(8192)
			connection.send(user_text)
			print(user_text.decode("utf8"))


host, port = ('', 7777)

socketServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socketServer.bind((host, port))

print("Server démarré...")

while True:
	print("En Écoute")
	socketServer.listen(5)
	connection, addresse = socketServer.accept()
	leThread = Thread_for_client(connection)
	leThread.start()

connection.close()
socketServer.close()