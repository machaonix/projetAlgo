#ifndef HG_LUDOTEQHE_H
#define HG_LUDOTEQHE_H

#include <stdio.h>
#include "TableauJeu.h"
#include "ListeEmpruntReservation.h"
#include "Adherant.h"


typedef enum {CHOIX_RESERVER=1, CHOIX_ANNULER_RESERVATION, CHOIX_EMPRUNTER, CHOIX_RETOUR_JEU, CHOIX_AFFICHE_JEU, CHOIX_TRIER_JEU, CHOIX_NOUV_ADHERANT, CHOIX_RENOUV_ADHERANT, CHOIX_AFFICHE_ADHERANT, CHOIX_AFFICHE_EMPRUNT, CHOIX_AFFICHE_RESERVATION, CHOIX_AFFICHE_RESERVATION_JEU, CHOIX_AFFICHE_EMPRUNT_JEU, CHOIX_SAUVEGARDER, CHOIX_QUITTER} ChoixAction;


void afficheMenu(void);

void Ludotheque(void);

void GLOBAL_RenouvellerAdherant(Adherant tAdherant[], unsigned int nbElemAdhearant);
void GLOBAL_NouvelAdherant(Adherant tAdherant[], unsigned int nbElemAdhearant);

void GLOBAL_Sauvegarder(TableauJeu* tabJeu, Adherant tAdherant[], unsigned int nbElemAdhearant, ListeReservation liste_Reservation, int nb_Reservation, ListeEmprunt liste_Emprunt, int nb_Emprunt);

void GLOBAL_afficherListeERJeu_Interactif(ListeER liste, TableauJeu* tabJeu, Bool isReservation);

Bool UTILE_Choix_O_N(char message[]);


#endif //HG_LUDOTEQHE_H
