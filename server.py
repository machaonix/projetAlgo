import socket
import threading
import sqlite3

class Thread_for_client(threading.Thread):
	def __init__(self, connection, curseur):
		threading.Thread.__init__(self)
		self.curseur = curseur
		self.connection = connection

	def run(self):
		user_pseudo = self.connection.recv(1024)
		while True:
			sql = f"""SELECT * FROM tMessages
					WHERE destinataire = '{user_pseudo}'
					ORDER BY dateDEnvoi
			"""
			userMessageconnection.recv(8192)
			resultat = curseur.excecute(sql)
			dernierMessage = resultat.fetchone()
			if(isinstance(dernierMessage, str))
				self.connection.send(dernierMessage.encode("utf8"))
			print(user_text.decode("utf8"))

#----------------------------------------------------------------------------------------------
#proKiloGramme principal



connexionALaBaseDeDonnees = sqlite3.connect('NOTRE_BASE_DE_DONNEES.db')
curseur = connexionALaBaseDeDonnees.cursor()
sql = """CREATE TABLE IF NOT EXISTS tMessages (
    expediteur VARCHAR(25) NOT NULL,
    destinataire VARCHAR(25),
    dateDEnvoi DATETIME DEFAULT NOW() NOT NULL,
    contenu VARCHAR(255) NOT NULL,
    idMessage INTEGER PRIMARY KEY  AUTO_INCREMENT
);"""
curseur.excecute(sql)
host, port = ('', 7777)

socketServer = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socketServer.bind((host, port))

print("Server démarré...")

while True:
	print("En Écoute")
	socketServer.listen(5) # <---- s'arrete et écoute 
	connection, addresse = socketServer.accept()# des qu'il trouve qqn il l'accepte
	leThread = Thread_for_client(connection, curseur)# declaration du thread
	leThread.start()# lancement du thread (ce qui il y a dans run())

connection.close()
socketServer.close()