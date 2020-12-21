#ifndef __EmpruntReservation_H__
#define __EmpruntReservation_H__

#include <stdio.h>
#include "Date.h"
#include "CodeErreur.h"

typedef struct
{
    unsigned int id;
    unsigned int idAdherant;//reference à une instance d'adherant
    unsigned int idJeu;//reference à une instance de jeu
    Date date;
} Emprunt, Reservation, EmpruntReservation;
//Pour les fonction communes EmpruntReservation sera utilise

EmpruntReservation lireEmpruntReservation(FILE* flux);
void afficherEmpruntReservation(EmpruntReservation *emprunt, FILE* flux);

//interactif
EmpruntReservation nouvEmpruntReservation(unsigned int id);

#endif //__EmpruntReservation_H__
