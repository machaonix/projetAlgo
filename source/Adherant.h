#ifndef HG_ADHERANT_H
#define HG_ADHERANT_H

#include <string.h>
#include <stdio.h>
#include "Bool.h"
#include "Date.h"
#include "CodeErreur.h"

#define PRIX_ADHERANT 15.00

typedef enum {HOMME, FEMME, INCONU} Civilite;

typedef struct
{
	unsigned int id;
	Civilite civilite;
	char nom[22];
	char prenom[22];
	Date dateInscri;
} Adherant;

/*
lireAdherant():

	Retour 		: retourne un adherant contenant les information du fichier adherant.don
	Arguments 	:
		flux -> Un pointeur de FILE en mode lecture représentant le fichier on sont enregistré les adherants
	Finalitée 	:
		Lire un Adherant dans un flux
*/
Adherant lireAdherant(FILE* flux);

/*
afficheAdherant():
	Retour 		: void
	Arguments 	:
		ad 			-> Un adherant à afficher
		flux		-> Un pointeur de FILE en mode écriture qui représente la sortie de l'affichage
		entete 		-> Valeur booleanne indiquant l'affichage d'une entête ou non
	Finalitée 	:
		Afficher un Adherant
*/
void afficheAdherant(Adherant ad, FILE* flux, Bool entete);

/*
nouvAdherant():
	Retour		: Un Adherant construit dans la fonction
	Arguments	:
		id			-> Un entier positif représantant l'identifiant du nouvel utilisateur
	Finalitée	:
		Créer un nouvel Adherant

*/
Adherant nouvAdherant(unsigned int id, Date dateDuJour);


//fonction sur tableau
/*
afficheTabAdherant():
	Retour 		: void
	arguments	:
		tAdherant 	-> Un tableau d'adherant contenant les adherant de la ludoteque
		nbElem 		-> Un entier repréentant le nombre d'adherant dans le tableau tAdherant
		flux		-> Un pointeur de FILE en mode écriture représantant la sortie sur la quelle écrire
		entete 		-> Un boolean informant de la volonter d'afficher une entête ou non
	Finalitée	:
		Afficher tout les Adhérants
*/
void afficheTabAdherant(Adherant tAdherant[], unsigned int nbElem, FILE* flux, Bool entete);


/*
insererAdherant():
	Retour 		: Taille du tableau avec le nouveau nombre d'elements ou un CodeErreur
	Arguments 	:
		tAdherant 	-> Un poiteur du tableau d'Adherant contenant tout les Adherant de la ludoteque
		nbElem 		-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
		tMax 		-> Un pointeur d'un entier positif représentant le nombre maximal d'Adherant de la ludoteque (la taille physique de tAdherant)
		ad 			-> Un Adherant a inserrer (la valeur est passer par adresse pour alleger le programe)
	Finalitée	:
		Ajouter un Adherant dans un tableau dynamiquement alloué
*/
int insererAdherant(Adherant* tAdherant[], unsigned int nbElem, unsigned int *tMax, Adherant* ad);

/*
supprimerAdherant():
	Retour 		: Taille du tableau avec le nouveau nombre d'elements ou un CodeErreur
	Arguments 	:
		tAdherant 	-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		nbElem 		-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
		ad 			-> Un Adherant a inserrer (la valeur est passer par adresse pour alleger le programe)
	Finalitée	:
		Supprimer un Adherant
*/
int supprimerAdherant(Adherant tAdherant[], unsigned int nbElem, Adherant* ad);

/*
decalageAGaucheAdherant()
	Retour		: void
	Arguments 	:
		tAdherant 	-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		debut 		-> Valeur entiere positive représentant l'index au quelle commancer le décalage
		nbElem 		-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
	Finalitée 	:
		"déplacer" les valeur de tAdherant en décremantant leurs indexs à partir de début jusqu'à nbElem dans l'optique de supprimer une valeur dans tAdherant
*/
void decalageAGaucheAdherant(Adherant tAdherant[], unsigned int debut, unsigned int nbElem);

/*
decalageADroiteAdherant()
	Retour		: void
	Arguments 	:
		tAdherant	-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		debut 		-> Valeur entiere positive représentant l'index au quelle commancer le décalage
		nbElem 		-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
	Finalitée 	:
		"déplacer" les valeur de tAdherant en incremantant leurs indexs à partir de début jusqu'à nbElem dans l'optique d'ajouter une nouvelle valeur dans tAdherant
*/
void decalageADroiteAdherant(Adherant tAdherant[], unsigned int debut, unsigned int nbElem);

/*
rechercherUnAdherant():
	Retour 		: index de l'element si ad a était trouvé ou l'index d'inserssion si ad n'a pas était trouvé
	Arguments 	:
		tAdherant 	-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		nbElem 		-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
		id 			-> Un id d'Adherant a rechercher
		trouve 		-> Un Bool passé par addresse (Si TRUE, adherant trouve sinon non)
	Finalitée :
		Retrouver un Adherant dans un tAdherant (trié) par recherche dichotomique
*/
unsigned int rechercherUnAdherant(Adherant tAdherant[], unsigned int nbElem, unsigned int id, Bool* trouve);

/*
chargerLesAdherants():
	Retour 		: retourne le nombre d'élément(s) stocké dans nomDuFichier
	Arguments 	:
		tAdherant 		-> Un poiteur du tableau d'Adherant contenant tout les Adherant de la ludoteque
		tMax 			-> Un pointeur d'un entier positif représentant le nombre maximal	d'Adherant de la ludoteque (la taille physique de tAdherant)
		nomDuFichier	-> Une chaine de caractere représentant le chemain du fichier stockant les Adherant
	Finalitée 	:
		Lire le fichier contenant les Adherant pour les stocker dans la mémoire centrale
*/
int chargerLesAdherants(Adherant* tAdherant[], unsigned int* tMax, char nomDuFichier[]);

/*
checkInscriptionValide():
	Retour		: retourne un boolean indiquant le validitée de l'inscription(si la differance entre la date du jour et la date d'insctiption est inferieur à 0)
	Arguments	:
		ad 			-> Un Adherant a rechercher (la valeur est passer par adresse pour alleger le programe)
		dateDuJour	-> Une Date repréntant la date du jour
	Finalitée	:
		Validée une insctiption
*/
Bool checkInscriptionValide(Adherant* ad, Date* dateDuJour);

/*
renouvelerInscription():

	Retour		: void
	Arguments 	:
		ad 				-> Un Adherant a rechercher (la valeur est passer par adresse pour alleger le programe et modifier ad)
		nouvelleDate	-> Nouvelle date à assigner à ad (la valeur est passer par adresse pour alleger le programe)
	Finalitée	:
		Faire qu'un Adherant soit valide
*/
void renouvelerInscription(Adherant* ad, Date* nouvelleDate);

/*
sauvegarderAdherant():
	Retour		: ERR_OUVERTURE_FICHIER | ERR_NO_ERR
	Arguments	:
		tAdherant		-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		nbElem 			-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
		nomDuFichier	-> Chemain vers un fichier pour y stocker les Adherants
	Finalitée:
		Enregister les Adherant
*/
CodeErreur sauvegarderAdherant(Adherant tAdherant[], unsigned int nbElem, char nomDuFichier[]);

/*
copieTabAdherant():
	Retour		: ERR_OUT_OF_RANGE | ERR_NO_ERR
	Arguments	:
		tAdherant1		-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		nbElem1			-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
		tAdherant2		-> Un tableau d'Adherant ou vont être copié les élements de tAdherant1
		tMax2 			-> Un entier positif représentant la taille physique de tAdherant2
	Finalitée	:
		Copier les elements d'un tableau dans un autre
*/
CodeErreur copieTabAdherant(Adherant tAdherant1[], unsigned int nbElem1, Adherant tAdherant2[], unsigned int tMax2);


unsigned int rechercherIDAdherantLibre(Adherant tAdherant[], unsigned int nbElem);
#endif //HG_ADHERANT_H
