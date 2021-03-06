#ifndef HG_EmpruntReservation_H
#define HG_EmpruntReservation_H

#include <stdio.h>
#include "Date.h"
#include "CodeErreur.h"

typedef struct
{
    unsigned int id;
    unsigned int idAdherent;//reference un adherent
    unsigned int idJeu;//reference à un jeu
    Date date;
} Emprunt, Reservation, EmpruntReservation;
//Pour les fonction communes EmpruntReservation sera utilise

EmpruntReservation lireEmpruntReservation(FILE* flux);//Lit un emprunt ou une réservation depuis un flux.
void afficherEmpruntReservation(EmpruntReservation *Empruntreservation, FILE* flux);//Affiche un emprunt ou une reservation dans un flux.
// *EmpruntReservation -> pointeur sur une structure pour que ça soit moins lourd

#endif //HG_EmpruntReservation_H
