#ifndef __JEU_H__
#define __JEU_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {TRI_NON_TRIE ,TRI_ID, TRI_NOM, TRI_TYPE, TRI_NB_EXEMPLAIRE_TOTAL, TRI_NB_EXEMPLAIRE_DISPO} TriSur;

typedef struct
{
    unsigned int id;
    char nom[41];
    char type[15];
    unsigned int nbExemplaireTotal;
    unsigned int nbExemplaireDispo;
} Jeu;

Jeu* lireJeu(FILE* flux);

//Flux=fichier pour sauvegarder ou Flux=STDOUT pour afficher en sortie standard
void afficheJeu(Jeu* jeu, FILE* flux);

//interactif
Jeu* nouvJeu(unsigned int id);

int jeuCmp(Jeu* j1, Jeu* j2, TriSur triSur);
void copyJeu(Jeu* jd, Jeu* js);

Jeu* allocJeu(void);

#endif //__JEU_H__
