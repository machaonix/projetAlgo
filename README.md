# projetAlgo

## TODO LIST

* Allan
	* s'ocupe des adherants
	* d'ocupe des dates
* Martin
	* s'ocuppe des jeux
* Mathis
	* s'occupe des listes



## Fonction d'utilisation du programme (et leurs dépandances) 
//Permet de voir ou créer ces fonctions

Charger les Fichiers (Adherant, ListeEmpruntReservation, TableauJeu)

Nouvel emprunt (ListeEmpruntReservation, TableauJeu, eventuellement Adherant pour resumé l'emrunt)
Retour emprunt (ListeEmpruntReservation, TableauJeu)

Nouvelle reservation (ListeEmpruntReservation)
Annule reservation (ListeEmpruntReservation)

Nouvel adherant (Adherant)
Renouveler adherant (Adherant)

Lister le catalogue de jeux (TableauJeu)

Lister les adherants ayant des emprunts en retard (Adherant, ListeEmpruntReservation)


## Variables dans la fonction globale (de ce que j'ai vu des fonctions de test)

Pour jeu:
	TableauJeu tabJeu
	CodeErreur cErr

Pour adherant:
	unsigned int nbMaxAdherant
	int nbAdherant
	Adherant* tabAdherant

Pour emprunt
	ListeEmprunt listeEmprunt
	ListeReservation listeReservation
