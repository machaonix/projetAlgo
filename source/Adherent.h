#ifndef HG_ADHERENT_H
#define HG_ADHERENT_H

#include <string.h>
#include <stdio.h>
#include "Bool.h"
#include "Date.h"
#include "CodeErreur.h"

#define PRIX_ADHERENT 15.00

typedef enum {HOMME, FEMME, INCONU} Civilite;

typedef struct
{
	unsigned int id;
	Civilite civilite;
	char nom[22];
	char prenom[22];
	Date dateInscri;
} Adherent;

/*
lireAdherent():

	Retour 		: retourne un adherent contenant les information du fichier adherent.don
	Paramètres 	:
		flux -> Un pointeur de FILE en mode lecture représentant le fichier on sont enregistré les adherents
	Finalitée 	:
		Lire un Adherent dans un flux
*/
Adherent lireAdherent(FILE* flux);

/*
afficheAdherent():
	Retour 		: void
	Paramètres 	:
		ad 			-> Un adherent à afficher
		flux		-> Un pointeur de FILE en mode écriture qui représente la sortie de l'affichage
		entete 		-> Valeur booleanne indiquant l'affichage d'une entête ou non
	Finalitée 	:
		Afficher un Adherent
*/
void afficheAdherent(Adherent ad, FILE* flux, Bool entete);

/*
nouvAdherent():
	Retour		: Un Adherent construit dans la fonction
	Paramètres	:
		id			-> Un entier positif représantant l'identifiant du nouvel utilisateur
		dateDuJour	-> Une date qui vas devenir la date d'inscription de l'Adherrant
	Finalitée	:
		Créer un nouvel Adherent

*/
Adherent nouvAdherent(unsigned int id, Date dateDuJour);


//fonction sur tableau
/*
afficheTabAdherent():
	Retour 		: void
	Paramètres	:
		tAdherent 	-> Un tableau d'adherent contenant les adherent de la ludoteque
		nbElem 		-> Un entier repréentant le nombre d'adherent dans le tableau tAdherent
		flux		-> Un pointeur de FILE en mode écriture représantant la sortie sur la quelle écrire
		entete 		-> Un boolean informant de la volonter d'afficher une entête ou non
	Finalitée	:
		Afficher tout les Adhérants
*/
void afficheTabAdherent(Adherent tAdherent[], unsigned int nbElem, FILE* flux, Bool entete);


/*
insererAdherent():
	Retour 		: Taille du tableau avec le nouveau nombre d'elements ou un CodeErreur
	Paramètres 	:
		tAdherent 	-> Un poiteur du tableau d'Adherent contenant tout les Adherent de la ludoteque
		nbElem 		-> Un entier posotif représentant le nombre d'Adherent de la ludoteque (de tAdherent)
		tMax 		-> Un pointeur d'un entier positif représentant le nombre maximal d'Adherent de la ludoteque (la taille physique de tAdherent)
		ad 			-> Un Adherent a inserrer (la valeur est passer par adresse pour alleger le programe)
	Finalitée	:
		Ajouter un Adherent dans un tableau dynamiquement alloué
*/
int insererAdherent(Adherent* tAdherent[], unsigned int nbElem, unsigned int *tMax, Adherent* ad);

/*
supprimerAdherent():
	Retour 		: Taille du tableau avec le nouveau nombre d'elements ou un CodeErreur
	Paramètres 	:
		tAdherent 	-> Un tableau d'Adherent contenant tout les Adherent de la ludoteque
		nbElem 		-> Un entier posotif représentant le nombre d'Adherent de la ludoteque (de tAdherent)
		id 			-> Un entier positif represantant l'id de l'adherent à supprimer
	Finalitée	:
		Supprimer un Adherent
*/
int supprimerAdherent(Adherent tAdherent[], unsigned int nbElem, unsigned int id);

/*
decalageAGaucheAdherent()
	Retour		: void
	Paramètres 	:
		tAdherent 	-> Un tableau d'Adherent contenant tout les Adherent de la ludoteque
		debut 		-> Valeur entiere positive représentant l'index au quelle commancer le décalage
		nbElem 		-> Un entier posotif représentant le nombre d'Adherent de la ludoteque (de tAdherent)
	Finalitée 	:
		"déplacer" les valeur de tAdherent en décremantant leurs indexs à partir de début jusqu'à nbElem dans l'optique de supprimer une valeur dans tAdherent
*/
void decalageAGaucheAdherent(Adherent tAdherent[], unsigned int debut, unsigned int nbElem);

/*
decalageADroiteAdherent()
	Retour		: void
	Paramètres 	:
		tAdherent	-> Un tableau d'Adherent contenant tout les Adherent de la ludoteque
		debut 		-> Valeur entiere positive représentant l'index au quelle commancer le décalage
		nbElem 		-> Un entier posotif représentant le nombre d'Adherent de la ludoteque (de tAdherent)
	Finalitée 	:
		"déplacer" les valeur de tAdherent en incremantant leurs indexs à partir de début jusqu'à nbElem dans l'optique d'ajouter une nouvelle valeur dans tAdherent
*/
void decalageADroiteAdherent(Adherent tAdherent[], unsigned int debut, unsigned int nbElem);

/*
rechercherUnAdherent():
	Retour 		: index de l'element si ad a était trouvé ou l'index d'inserssion si ad n'a pas était trouvé
	Paramètres 	:
		tAdherent 	-> Un tableau d'Adherent contenant tout les Adherent de la ludoteque
		nbElem 		-> Un entier posotif représentant le nombre d'Adherent de la ludoteque (de tAdherent)
		id 			-> Un id d'Adherent a rechercher
		trouve 		-> Un Bool passé par addresse (Si TRUE, adherent trouve sinon FALSE)
	Finalitée :
		Retrouver un Adherent dans un tAdherent (trié) par recherche dichotomique
*/
unsigned int rechercherUnAdherent(Adherent tAdherent[], unsigned int nbElem, unsigned int id, Bool* trouve);

/*
chargerLesAdherents():
	Retour 		: retourne le nombre d'élément(s) stocké dans nomDuFichier
	Paramètres 	:
		tAdherent 		-> Un poiteur du tableau d'Adherent contenant tout les Adherent de la ludoteque
		tMax 			-> Un pointeur d'un entier positif représentant le nombre maximal	d'Adherent de la ludoteque (la taille physique de tAdherent)
		nomDuFichier	-> Une chaine de caractere représentant le chemain du fichier stockant les Adherent
	Finalitée 	:
		Lire le fichier contenant les Adherent pour les stocker dans la mémoire centrale
*/
int chargerLesAdherents(Adherent* tAdherent[], unsigned int* tMax, char nomDuFichier[]);

/*
checkInscriptionValide():
	Retour		: retourne un boolean indiquant le validitée de l'inscription(si la differance entre la date du jour et la date d'insctiption est inferieur à 0)
	Paramètres	:
		ad 			-> Un Adherent a rechercher (la valeur est passer par adresse pour alleger le programe)
		dateDuJour	-> Une Date repréntant la date du jour
	Finalitée	:
		Validée une insctiption
*/
Bool checkInscriptionValide(Adherent* ad, Date* dateDuJour);

/*
renouvelerInscription():

	Retour		: ERR_OPERATION_INVALIDE | ERR_NO_ERR
	Paramètres 	:
		ad 				-> Un Adherent a rechercher (la valeur est passer par adresse pour alleger le programe et modifier ad)
		nouvelleDate	-> Nouvelle date à assigner à ad (la valeur est passer par adresse pour alleger le programe)
	Finalitée	:
		Faire qu'un Adherent soit valide
*/
CodeErreur renouvelerInscription(Adherent* ad, Date* nouvelleDate);

/*
sauvegarderAdherent():
	Retour		: ERR_OUVERTURE_FICHIER | ERR_NO_ERR
	Paramètres	:
		tAdherent		-> Un tableau d'Adherent contenant tout les Adherent de la ludoteque
		nbElem 			-> Un entier posotif représentant le nombre d'Adherent de la ludoteque (de tAdherent)
		nomDuFichier	-> Chemain vers un fichier pour y stocker les Adherents
	Finalitée:
		Enregister les Adherent
*/
CodeErreur sauvegarderAdherent(Adherent tAdherent[], unsigned int nbElem, char nomDuFichier[]);

/*
copieTabAdherent():
	Retour		: ERR_OUT_OF_RANGE | ERR_NO_ERR
	Paramètres	:
		tAdherent1		-> Un tableau d'Adherent contenant tout les Adherent de la ludoteque
		nbElem1			-> Un entier posotif représentant le nombre d'Adherent de la ludoteque (de tAdherent)
		tAdherent2		-> Un tableau d'Adherent ou vont être copié les élements de tAdherent1
		tMax2 			-> Un entier positif représentant la taille physique de tAdherent2
	Finalitée	:
		Copier les elements d'un tableau dans un autre
*/
CodeErreur copieTabAdherent(Adherent tAdherent1[], unsigned int nbElem1, Adherent tAdherent2[], unsigned int tMax2);

/*
rechercherIDAdherentLibre():
	Retour		: Premier id disponible
	Paramètres	:
		tAdherent1		-> Un tableau d'Adherent contenant tout les Adherent de la ludoteque
		nbElem 			-> Un entier posotif représentant le nombre d'Adherent de la ludoteque (de tAdherent)
	Finalitée	:
		Trouver le plus petit id disponible possible pour eviter d'avoir des ecarts entre les id d'Adherent
*/
unsigned int rechercherIDAdherentLibre(Adherent tAdherent[], unsigned int nbElem);
#endif //HG_ADHERENT_H
