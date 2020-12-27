#ifndef __LISTEEMPRUNTRESERVATION_H__
#define __LISTEEMPRUNTRESERVATION_H__

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
Bool listeER_estVide(ListeEmprunt liste); //TRUE si vide

void afficherListeEmpruntReservation(ListeER liste, FILE* flux);
void afficherListeERJeu(ListeER liste, unsigned int idJeu); //afficher reservation pour un jeu données
ListeER chargerListeEmprunReservation(char nomDeFichier[]);
// Retourne une liste
*Element chargercreerMaillon(FILE *flux); // Retourne un pointeur vers l'élément suivant (défini element.suiv)

ListeER rechercherListeEmpruntReservation(ListeER liste, unsigned int id);

ListeER insererEmpruntReservation(ListeER liste, Emprunt element);
ListeER insererDevantEmpruntReservation(ListeER liste, Emprunt er);

ListeER supprimerEmpruntReservation(ListeER liste, Emprunt element);
ListeER supprimerDevantEmpruntReservation(ListeER liste);

ListeER supprimerListe(ListeER liste); //supprime toutes la liste est retourne NULL;

#endif //__LISTEEMPRUNTRESERVATION_H__
