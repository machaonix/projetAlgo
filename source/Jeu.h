#ifndef __JEU_H__
#define __JEU_H__

#include <stdio.h>
#include <string.h>
#include "CodeErreur.h"

typedef enum {CONSTRUCTION, PLATEAU, TUILE, CARTE, LOGIQUE} TypeJeu;

typedef enum {TRI_ID, TRI_NOM, TRI_TYPE, TRI_NB_EXEMPLAIRE_TOTAL, TRI_NB_EXEMPLAIRE_DISPO} TriSur;

typedef struct
{
    unsigned int id;
    char nom[41];
    TypeJeu type;
    unsigned int nbExemplaireTotal;
    unsigned int nbExemplaireDispo;
} Jeu;

//Fonction sur Jeu
Jeu lireJeu(FILE* flux);
void afficheJeu(Jeu* jeu, FILE* flux);
Jeu nouvJeu(unsigned int id);

//Fonction sur le tableau de Jeu
int retirerJeu(Jeu* tJeu[], int nbElem, unsigned int idJeu);
int ajouterJeu(Jeu* tJeu[], int nbElem, Jeu jeu);

int rechercherJeu(Jeu* tJeu[], int nbElem, unsigned idJeu);

void copyTab(Jeu* tSource[], unsigned int debut, unsigned int fin, Jeu* tDest[]);
void fusionTabJeu(Jeu* tSource1[], unsigned int taille1, Jeu* tSource2[], unsigned int taille2, TriSur triSur, Jeu* tDest[]);
int triJeu(Jeu* tJeux[], unsigned int taille, TriSur triSur);

#endif //__JEU_H__
