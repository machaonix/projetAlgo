#ifndef __ADHERANT_H__
#define __ADHERANT_H__

#include <string.h>
#include <stdio.h>
#include "Bool.h"
#include "Date.h"
#include "CodeErreur.h"

#define PRIX_ADHERANT 15

typedef enum {HOMME, FEMME} Civilite;

typedef struct 
{
	unsigned int id;
	Civilite civilite;
	char nom[20];
	char prenom[20];
	Date dateInscri;
} Adherant;

Adherant lireAdherant(FILE* flux);
void afficheAdherant(Adherant ad, FILE* flux);
Adherant nouvAdherant(unsigned int id);

//fonction sur tableau
void afficheTabAdherant(Adherant tAdherant[], int nbElem);

//retourne la taille du tableau ou un CodeErreur
int insererAdherant(Adherant tAdherant[], int nbElem, Adherant ad);
int supprimerAdherant(Adherant tAdherant[], int nbElem, Adherant ad);

void decalageAGaucheAdherant(Adherant tAdherant[], int debut, int nbElem);
void decalageADroiteAdherant(Adherant tAdherant[], int debut, int nbElem);

Bool checkInscriptionValide(Adherant ad);
void renouvelerInscription(Adherant ad, Date nouvelleDate);

#endif //__ADHERANT_H__
