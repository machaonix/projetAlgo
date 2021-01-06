#ifndef HG_LISTEEMPRUNTRESERVATION_H
#define HG_LISTEEMPRUNTRESERVATION_H

#include <stdlib.h>
#include <stdio.h>
#include "Bool.h"
#include "EmpruntReservation.h"

typedef struct element
{
	EmpruntReservation empRes;
	struct element* suiv;
} Element, *ListeReservation, *ListeEmprunt, *ListeER;
//Pour les fonctions communes ListeER sera utilise

ListeER listeER_Vide(void); //Créer une nouvelle liste
Bool listeER_estVide(ListeER liste); //TRUE si vide

void afficherListeEmpruntReservation(ListeER liste, FILE* flux,int nb);
void afficherListeERJeu(ListeER liste, unsigned int idJeu); //afficher reservation pour un jeu données
ListeER chargerListeEmpruntReservation(char nomDeFichier[], unsigned int *nb);

unsigned int rechercherIdLibre(ListeER liste); //retourne le premier ID de libre

ListeER insererEmpruntReservation(ListeER liste, unsigned int *nb, EmpruntReservation er);
//Il faut vérifier si on peux bien emprunter le jeu;
ListeER insererDevantEmpruntReservation(ListeER liste, EmpruntReservation er);

ListeER supprimerEmpruntReservation(ListeER liste, unsigned int id, int *nb);
ListeER supprimerDevantEmpruntReservation(ListeER liste);

ListeER supprimerListe(ListeER liste); //supprime toutes la liste est retourne NULL;

CodeErreur sauvegarderListeER(ListeER liste, char nomDeFichier[], int nb);

Bool reservationExiste(ListeER liste, unsigned int id, unsigned int idJeu);

#endif //HG_LISTEEMPRUNTRESERVATION_H
