#ifndef HG_DATE_H
#define HG_DATE_H

#include <stdio.h>
#include <stdlib.h>
#include "CodeErreur.h"

typedef struct {
  int jour;
  int mois;
  int annee;
} Date;

/*
lireDate():
    Retour		: Une date lue dans un flux
    Argument	:
        flux -> Un pointeur vers un flux en mode lecture ou le cursseur se trouve juste avant la date
	Finalitée	:
		Lire une date dans un flux
*/
Date lireDate(FILE* flux);

/*
afficherDate():
	Retour 		: void
	Arguments	:
		date -> Une date à afficher
		flux -> Un pointeur de flux en mode écriture où ecrire date
	Finalité:
		Ecrire une date sur un flux
*/
void afficherDate(Date date, FILE* flux);

/*
dateCmp():
	Retour 		: ecart en jour (date1 - date2)
	Arguments	:
		date1 -> Une Date destinée à être comparée avec date2
		date2 -> Une Date destinée à être comparée avec date1
	Finalité:
		Comparer 2 dates
*/
int dateCmp(Date date1, Date date2);

/*
plusPetiteDate():
	Retour 		: Pointeur de la Date la plus petite
	Arguments	:
		date1 -> Un pointeur de Date destinée à être comparée avec date2
		date2 -> Un pointeur de Date destinée à être comparée avec date1
	Finalité :
			Déterminer la plus petite date
*/
Date *plusPetiteDate(Date *date1, Date *date2);

/*
plusGrandeDate():
	Retour 		: Pointeur de la Date la plus grande
	Arguments	:
		date1 -> Un pointeur de Date destinée à être comparée avec date2
		date2 -> Un pointeur de Date destinée à être comparée avec date1
	Finalité :
			Déterminer la plus grande date
*/
Date *plusGrandeDate(Date *date1, Date *date2);

#endif //HG_DATE_H
