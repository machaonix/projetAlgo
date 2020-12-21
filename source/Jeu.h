#ifndef __JEU_H__
#define __JEU_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CodeErreur.h"

typedef enum {TRI_ID, TRI_NOM, TRI_TYPE, TRI_NB_EXEMPLAIRE_TOTAL, TRI_NB_EXEMPLAIRE_DISPO} TriSur;

typedef struct
{
    unsigned int id;
    char nom[41];
    char type[15];
    unsigned int nbExemplaireTotal;
    unsigned int nbExemplaireDispo;
} Jeu;

//Fonction sur Jeu
Jeu lireJeu(FILE* flux);
void afficheJeu(Jeu* jeu, FILE* flux);
Jeu nouvJeu(unsigned int id);

//Fonction sur le tableau de Jeu
//Flux=fichier pour sauvegarder ou Flux=STDOUT pour afficher en sortie standard
void afficheTabJeu(Jeu* tJeu[], int nbElem, FILE* flux);

int chargerTabJeu(Jeu* tJeu[], char nomFichier[], int nbElemMax);

//retourne la taille du tableau ou une erreur
int retirerJeu(Jeu* tJeu[], int nbElem, unsigned int idJeu);
int ajouterJeu(Jeu* tJeu[], int nbElem, Jeu jeu, int nbElemMax);

//retourne le rang du jeu trouvé ou NOT_FOUND
int rechercherJeu(Jeu* tJeu[], int nbElem, unsigned int idJeu);

//n'est pas fait pour etre utilisé par d'autres fonctions que triJeu
void copyTab(Jeu* tSource[], unsigned int debut, unsigned int fin, Jeu* tDest[]);
void fusionTabJeu(Jeu* tSource1[], unsigned int nbElem1, Jeu* tSource2[], unsigned int nbElem2, TriSur triSur, Jeu* tDest[]);

//tri tJeu et retourne
void triJeu(Jeu* tJeux[], unsigned int nbElem, TriSur triSur);

#endif //__JEU_H__
