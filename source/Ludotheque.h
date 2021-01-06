#ifndef HG_LUDOTEQHE_H
#define HG_LUDOTEQHE_H

#include <stdio.h>
#include "TableauJeu.h"
#include "ListeEmpruntReservation.h"
#include "Adherant.h"


typedef enum {CHOIX_ANNULER_RESERVATION =1 , CHOIX_EMPRUNTER, CHOIX_RETOUR_JEU, CHOIX_AFFICHE_JEU, CHOIX_TRIER_JEU, CHOIX_AJOUTER_JEU, CHOIX_MODIFIER_SUPPRIMER_JEU, CHOIX_NOUV_ADHERANT, CHOIX_RENOUV_ADHERANT, CHOIX_AFFICHE_ADHERANT, CHOIX_AFFICHE_EMPRUNT, CHOIX_AFFICHE_RESERVATION, CHOIX_AFFICHE_RESERVATION_JEU, CHOIX_AFFICHE_EMPRUNT_JEU, CHOIX_SAUVEGARDER, CHOIX_QUITTER} ChoixAction;


void afficheMenu(void);

void Ludotheque(void);


Bool GLOBAL_Emprunter(ListeReservation* liste_Reservation, unsigned int* nb_Reservation, ListeEmprunt* liste_Emprunt, unsigned int* nb_Emprunt, TableauJeu* tabJeu, Adherant* tAdherant[], int* nbElemAdhearant, unsigned int* tMaxAdherant, Date dateDuJour);

Bool GLOBAL_RenouvellerAdherant(Adherant tAdherant[], unsigned int nbElemAdhearant);
Bool GLOBAL_NouvelAdherant(Adherant* tAdherant[], int* nbElemAdhearant, unsigned int* tMaxAdherant, unsigned int* rangNouvAdherant, Date dateDuJour);

void GLOBAL_Sauvegarder(TableauJeu* tabJeu, Adherant tAdherant[], unsigned int nbElemAdhearant, ListeReservation liste_Reservation, int nb_Reservation, ListeEmprunt liste_Emprunt, int nb_Emprunt);

void GLOBAL_afficherListeERJeu_Interactif(ListeER liste, TableauJeu* tabJeu, Bool isReservation);

Bool UTILE_Choix_O_N(char message[]);

void UTILE_InitNbJeuDispo(ListeEmprunt liste_Emprunt,  TableauJeu* tabJeu);

#endif //HG_LUDOTEQHE_H
