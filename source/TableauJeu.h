#ifndef HG_TABLEAUJEU_H
#define HG_TABLEAUJEU_H

#include <stdlib.h>
#include <stdio.h>
#include "Jeu.h"
#include "CodeErreur.h"
#include "Bool.h"
#include "ioUtilitaire.h"

#define TAILLE_MAX_TAB_JEU 100

typedef struct
{
	unsigned int nbElement;
	ElementJeu triSur;
	Jeu* jeux[TAILLE_MAX_TAB_JEU];
} TableauJeu;

//initialise les variables du tableau
void initTabJeu(TableauJeu* tabJeu);
void libererTabJeu(TableauJeu* tabJeu);

void afficheTabJeu(TableauJeu* tabJeu, FILE* flux);
void affichePartieTabJeu(TableauJeu* tabJeu, unsigned int begin, unsigned int end, FILE* flux);

//retourne 0 ou un CodeErreur
CodeErreur chargerTabJeu(TableauJeu* tabJeu, char nomFichier[]);
CodeErreur sauvegarderTabJeu(TableauJeu* tabJeu, char nomFichier[]);

Bool jeuDisponible(TableauJeu* tabJeu, Jeu* jeu);
unsigned int genIdJeu(TableauJeu* tabJeu);

CodeErreur rechercherJeuInteractif(TableauJeu* tabJeu, Bool* trouve, unsigned int* rang);
//retourne le rang du jeu trouvé ou le rang d'insertion si non trouvé
//Bool* trouve est assigné a TRUE si trouvé à FALSE sinon
unsigned int rechercherJeu(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve, Bool cherchePremier);
//les fonctions suivantes sont utilisé en interne par rechercherIdJeu
unsigned int _rechercherPremierJeu_TabNonTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve);
unsigned int _rechercherDernierJeu_TabNonTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve);
unsigned int _rechercherPremierJeu_TabTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve);
unsigned int _rechercherDernierJeu_TabTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve);

void triTabJeuInteractif(TableauJeu* tabJeu);
void triTabJeu(TableauJeu* tabJeu, ElementJeu elementJeu);
//les fonctions suivantes sont utilisé en interne par triTabJeu
void _triJeu(Jeu* tSource[], unsigned int nbElem, ElementJeu elementJeu);
void copyTabJeu(Jeu* tSource[], unsigned int debut, unsigned int fin, Jeu* tDest[]);
void fusionTabJeu(Jeu* tSource1[], unsigned int nbElem1, Jeu* tSource2[], unsigned int nbElem2, ElementJeu elementJeu, Jeu* tDest[]);

//retourne un CodeErreur
CodeErreur retirerJeu(TableauJeu* tabJeu, Jeu* jeu);
CodeErreur retirerJeuInteractif(TableauJeu* tabJeu);
//Retourne un CodeErreur
CodeErreur ajouterJeu(TableauJeu* tabJeu, Jeu* jeu);
CodeErreur ajouterJeuInteractif(TableauJeu* tabJeu);
//les fonctions suivantes sont utilisé en interne par retirerJeu et ajouterJeu
void _decalageAGaucheJeu(TableauJeu* tabJeu, unsigned int debut);//ne libere pas la memoire
void _decalageADroiteJeu(TableauJeu* tabJeu, unsigned int debut);

#endif //HG_TABLEAUJEU_H
