#ifndef __LISTEEMPRUNTRESERVATION_H__
#define __LISTEEMPRUNTRESERVATION_H__

#include <stdlib.h>
#include <stdio.h>
#include "Bool.h"
#include "EmpruntReservation.h"

typedef struct element
{
	EmpruntReservation valeur;
	struct element* suiv;
} Element, *ListeReservation, *ListeEmprunt, *ListeER;
//Pour les fonctions communes ListeER sera utilise

ListeER listeER_Vide(void);
Bool listeER_estVide(ListeEmprunt liste);

void afficherListeEmpruntReservation(ListeER liste, FILE* flux);
void afficherListeERJeu(ListeER liste, FILE* flux, unsigned int idJeu);
ListeER chargerListeEmprunResevarion(char nomDeFichier[]);

void rechercherListeEmpruntReservation(ListeER liste, Element element); //plusieurs emprunts peuvent exister pour un même jeu

ListeER insererEmpruntReservation(ListeER liste, Emprunt element);
ListeER insererDevantEmpruntReservation(ListeER liste, Emprunt element);

ListeER supprimerEmpruntReservation(ListeER liste, Emprunt element);
ListeER supprimerDevantEmpruntReservation(ListeER liste);

#endif //__LISTEEMPRUNTRESERVATION_H__