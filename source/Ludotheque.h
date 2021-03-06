#ifndef HG_LUDOTEQHE_H
#define HG_LUDOTEQHE_H

#include <stdio.h>
#include "TableauJeu.h"
#include "ListeEmpruntReservation.h"
#include "Adherent.h"
#include "ioUtilitaire.h"


typedef enum {CHOIX_ANNULER_RESERVATION =1 , CHOIX_EMPRUNTER, CHOIX_RETOUR_JEU, CHOIX_AFFICHE_JEU, CHOIX_TRIER_JEU, CHOIX_AJOUTER_JEU, CHOIX_MODIFIER_SUPPRIMER_JEU, CHOIX_NOUV_ADHERANT, CHOIX_RENOUV_ADHERANT, CHOIX_AFFICHE_ADHERANT, CHOIX_AFFICHE_EMPRUNT, CHOIX_AFFICHE_RESERVATION, CHOIX_AFFICHE_RESERVATION_JEU, CHOIX_AFFICHE_EMPRUNT_JEU, CHOIX_SAUVEGARDER, CHOIX_QUITTER} ChoixAction;


void afficheMenu(void);

void Ludotheque(void);

Bool GLOBAL_Anuller_Reservation(ListeReservation* lr, unsigned int* nb_Reservation, Adherent tAdherent[], unsigned int nbElemAdherent, TableauJeu* tabJeu);
Bool GLOBAL_Emprunter(ListeReservation* liste_Reservation, unsigned int* nb_Reservation, ListeEmprunt* liste_Emprunt, unsigned int* nb_Emprunt, TableauJeu* tabJeu, Adherent* tAdherent[], int* nbElemAdherent, unsigned int* tMaxAdherent, Date dateDuJour);
Bool GLOBAL_RetourJeu(Adherent tAdherent[], unsigned int nbElemAdherent, TableauJeu* tabJeu, ListeEmprunt* liste_Emprunt, unsigned int* nb_Emprunt, ListeReservation* liste_Reservation, Date dateDuJour);

Bool GLOBAL_RenouvellerAdherent(Adherent tAdherent[], unsigned int nbElemAdherent, Date dateDuJour);
Bool GLOBAL_NouvelAdherent(Adherent* tAdherent[], int* nbElemAdherent, unsigned int* tMaxAdherent, unsigned int* rangNouvAdherent, Date dateDuJour);

Bool GLOBAL_Sauvegarder(TableauJeu* tabJeu, Adherent tAdherent[], unsigned int nbElemAdherent, ListeReservation liste_Reservation, int nb_Reservation, ListeEmprunt liste_Emprunt, int nb_Emprunt);

void GLOBAL_afficherListeERJeu_Interactif(ListeER liste, TableauJeu* tabJeu, Bool isReservation);

Bool GLOBAL_ModifierSupprimerJeu(TableauJeu* tabJeu, ListeReservation* liste_Reservation, unsigned int *nb_Reservation, ListeEmprunt liste_Emprunt);

void UTILE_InitNbJeuDispo(ListeEmprunt liste_Emprunt,  TableauJeu* tabJeu);

#endif //HG_LUDOTEQHE_H
