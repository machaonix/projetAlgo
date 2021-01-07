#ifndef HG_JEU_H
#define HG_JEU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CodeErreur.h"
#include "Bool.h"

typedef enum { ELEM_JEU_NONE , ELEM_JEU_ID, ELEM_JEU_NOM, ELEM_JEU_TYPE, ELEM_JEU_NB_EXEMPLAIRE_TOTAL, ELEM_JEU_NB_EXEMPLAIRE_DISPO} ElementJeu;

ElementJeu choisirElementJeu(char utilite[]);
Bool elementJeuExiste(ElementJeu elementJeu, Bool noneAutorisee);
void afficheAllElementJeu();

typedef struct
{
    unsigned int id;
    char nom[41];
    char type[15];
    unsigned int nbExemplaireTotal;
    unsigned int nbExemplaireDispo;
} Jeu;

Jeu* lireJeu(FILE* flux);
CodeErreur entrerValeurElementJeu(Jeu* jeu, ElementJeu elementJeu);

//Flux=fichier pour sauvegarder ou Flux=STDOUT pour afficher en sortie standard
void afficheJeu(Jeu* jeu, FILE* flux);

//interactif
Jeu* nouvJeu(unsigned int id);

int jeuCmp(Jeu* j1, Jeu* j2, ElementJeu elementJeu);

void copyJeu(Jeu* jd, Jeu* js);

Jeu* allocJeu(void);

#endif //HG_JEU_H
