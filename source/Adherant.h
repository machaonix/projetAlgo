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

Adherant lireAdherant(FILE* flux);
void afficheAdherant(Adherant ad, FILE* flux, Bool entete);
Adherant nouvAdherant(unsigned int id);


//fonction sur tableau

/*
	Retour 		: NULL
	arguments	:
		tAdherant 	-> Un tableau d'adherant contenant les adherant de la ludoteque
		nbElem 		-> Un entier repréentant le nombre d'adherant dans le tableau tAdherant
		flux		-> Un FILE représantant la sortie sur la quelle écrire
		entete 		-> Un boolean informant de la volonter d'afficher une entête ou non
*/
void afficheTabAdherant(Adherant tAdherant[], unsigned int nbElem, FILE* flux, Bool entete);

//retourne la taille du tableau ou un CodeErreur
int insererAdherant(Adherant tAdherant[], unsigned int nbElem, unsigned int *tMax, Adherant* ad);
int supprimerAdherant(Adherant tAdherant[], unsigned int nbElem, Adherant* ad);

void decalageAGaucheAdherant(Adherant tAdherant[], unsigned int debut, unsigned int nbElem);
void decalageADroiteAdherant(Adherant tAdherant[], unsigned int debut, unsigned int nbElem);
int rechercherUnAdherant(Adherant tAdherant[], unsigned int nbElem, Adherant* ad, CodeErreur* trouve);
int chargerLesAdherants(Adherant tAdherant[], unsigned int *tMax, char nomDuFichier[]);


Bool checkInscriptionValide(Adherant ad);
void renouvelerInscription(Adherant ad, Date nouvelleDate);

#endif //__ADHERANT_H__
