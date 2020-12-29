#ifndef __ADHERANT_H__
#define __ADHERANT_H__

#include <string.h>
#include <stdio.h>
#include "Bool.h"
#include "Date.h"
#include "CodeErreur.h"

#define PRIX_ADHERANT 15

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
		flux -> Un pointeur de FILE représentant le fichier on sont enregistré les adherants
*/
Adherant lireAdherant(FILE* flux);

/*
afficheAdherant():
	Retour 		: NULL
	Arguments 	:
		ad 			-> Un adherant à afficher
		flux		-> Un pointeur de FILE qui représente la sortie de l'affichage
		entete 		-> Valeur booleanne indiquant l'affichage d'une entête ou non
*/
void afficheAdherant(Adherant ad, FILE* flux, Bool entete);

/*
nouvAdherant():
	Retour		: Un Adherant construit dans la fonction
	Arguments	:
		id			-> Un entier positif représantant l'identifiant du nouvel utilisateur
*/
Adherant nouvAdherant(unsigned int id);


//fonction sur tableau

/*
afficheTabAdherant():
	Retour 		: NULL
	arguments	:
		tAdherant 	-> Un tableau d'adherant contenant les adherant de la ludoteque
		nbElem 		-> Un entier repréentant le nombre d'adherant dans le tableau tAdherant
		flux		-> Un FILE représantant la sortie sur la quelle écrire
		entete 		-> Un boolean informant de la volonter d'afficher une entête ou non
*/
void afficheTabAdherant(Adherant tAdherant[], unsigned int nbElem, FILE* flux, Bool entete);


/*
insererAdherant():
	Retour 		: Taille du tableau avec le nouveau nombre d'elements ou un CodeErreur
	Arguments 	:
		tAdherant 	-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		nbElem 		-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
		tMax 		-> Un pointeur d'un entier positif représentant le nombre maximal	d'Adherant de la ludoteque (la taille physique de tAdherant)
		ad 			-> Un Adherant a inserrer (la valeur est passer par adresse pour alleger le programe)
*/
int insererAdherant(Adherant tAdherant[], unsigned int nbElem, unsigned int *tMax, Adherant* ad);

/*
supprimerAdherant():
	Retour 		: Taille du tableau avec le nouveau nombre d'elements ou un CodeErreur
	Arguments 	:
		tAdherant 	-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		nbElem 		-> Un entier posotif représentant le nombre d'Adherant de la ludoteque (de tAdherant)
		ad 			-> Un Adherant a inserrer (la valeur est passer par adresse pour alleger le programe)
*/
int supprimerAdherant(Adherant tAdherant[], unsigned int nbElem, Adherant* ad);

/*
decalageAGaucheAdherant()
	Retour		: Null
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
	Retour		: Null
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
		ad 			-> Un Adherant a rechercher (la valeur est passer par adresse pour alleger le programe)
		trouve 		-> Un CodeErreur passé par addresse (deux valeur possible : ERR_NOT_FOUND | ERR_EXISTE_DEJA)
	Finalitée :
		Retrouver un Adherant dans un tAdherant (trié) par recherche dichotomique
*/
int rechercherUnAdherant(Adherant tAdherant[], unsigned int nbElem, Adherant* ad, CodeErreur* trouve);

/*
chargerLesAdherants():
	Retour 		: retourne le nombre d'élément(s) stocké dans nomDuFichier
	Arguments 	:
		tAdherant 		-> Un tableau d'Adherant contenant tout les Adherant de la ludoteque
		tMax 			-> Un pointeur d'un entier positif représentant le nombre maximal	d'Adherant de la ludoteque (la taille physique de tAdherant)
		nomDuFichier	-> Une chaine de caractere représentant le chemain du fichier stockant les Adherant
	Finalitée 	:
		Lire le fichier contenant les Adherant pour les stocker dans la mémoire centrale
*/
int chargerLesAdherants(Adherant tAdherant[], unsigned int *tMax, char nomDuFichier[]);

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

	Retour		: NULL
	Arguments 	:
		ad 				-> Un Adherant a rechercher (la valeur est passer par adresse pour alleger le programe et modifier ad)
		nouvelleDate	-> Nouvelle date à assigner à ad (la valeur est passer par adresse pour alleger le programe)
*/
void renouvelerInscription(Adherant* ad, Date* nouvelleDate);

CodeErreur sauvegarderAdherant(Adherant tAdherant[], unsigned int nbElem, char nomDuFichier[]);

#endif //__ADHERANT_H__
