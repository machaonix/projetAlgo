#ifndef __TABLEAUJEU_H__
#define __TABLEAUJEU_H__

#include <stdlib.h>
#include <stdio.h>
#include "Jeu.h"
#include "CodeErreur.h"
#include "Bool.h"

#define TAILLE_MAX_TAB_JEU 32

typedef struct 
{
	unsigned int nbElement;
	TriSur triSur;
	Jeu* jeux[TAILLE_MAX_TAB_JEU];
} TableauJeu;

//initialise les variables du tableau 
void initTabJeu(TableauJeu* tabJeu);

void afficheTabJeu(TableauJeu* tabJeu, FILE* flux);

//retourne 0 ou un CodeErreur
CodeErreur chargerTabJeu(TableauJeu* tabJeu, char nomFichier[]);
CodeErreur sauvegarderTabJeu(TableauJeu* tabJeu, char nomFichier[]);

Bool jeuDisponible(TableauJeu* tabJeu, unsigned int id);

void libererTabJeu(TableauJeu* tabJeu);

//retourne le rang du jeu trouvé ou le rang d'insertion si non trouvé
//Bool* trouve est assigné a TRUE si trouvé à FALSE sinon 
unsigned int rechercherIdJeu(TableauJeu* tabJeu, unsigned int idJeu, Bool* trouve);
//les fonctions suivantes sont utilisé en interne par rechercherIdJeu
int _rechercherIdJeu_TabNonTrie(TableauJeu* tabJeu, unsigned int idJeu);
unsigned int _rechercherIdJeu_TabTriId(TableauJeu* tabJeu, unsigned int idJeu, Bool* trouve);


unsigned int genIdJeu(TableauJeu* tabJeu);

//retourne 0 ou un CodeErreur
CodeErreur retirerJeu(TableauJeu* tabJeu, unsigned int idJeu);
CodeErreur retirerJeuInteractif(TableauJeu* tabJeu);

//retourne 0 si l'ajout est fait
//sinon retourne un CodeErreur 
CodeErreur ajouterJeu(TableauJeu* tabJeu, Jeu* jeu);
CodeErreur ajouterJeuInteractif(TableauJeu* tabJeu);

//les fonctions suivantes sont utilisé en interne par retirerJeu et ajouterJeu
void _decalageAGaucheJeu(TableauJeu* tabJeu, unsigned int debut);//ne libere pas la memoire
void _decalageADroiteJeu(TableauJeu* tabJeu, unsigned int debut);



//tri tJeu et retourne
void triTabJeu(TableauJeu* tabJeu, TriSur triSur);


//les fonctions suivantes sont utilisé en interne par triTabJeu
void copyTabJeu(Jeu* tSource[], unsigned int debut, unsigned int fin, Jeu* tDest[]);
void fusionTabJeu(Jeu* tSource1[], unsigned int nbElem1, Jeu* tSource2[], unsigned int nbElem2, TriSur triSur, Jeu* tDest[]);
void _triJeu(Jeu* tSource[], unsigned int nbElem, TriSur triSur);

#endif //__TABLEAUJEU_H__
