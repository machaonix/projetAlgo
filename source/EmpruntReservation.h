#ifndef __EmpruntReservation_H__
#define __EmpruntReservation_H__

#include <stdio.h>
#include "Date.h"


typedef struct
{
    unsigned int id;
    unsigned int idAdherant;//reference à une instance d'adherant
    unsigned int idJeu;//reference à une instance de jeu
    Date date;
} Emprunt, Reservation;
//Pour les fonction communes Emprunt sera utilise

Emprunt lireEmpruntReservation(FILE* flux);
void afficherEmpruntReservation(Emprunt *emprunt, FILE* flux);
Emprunt nouvEmpruntReservation(unsigned int id);

#endif //__EmpruntReservation_H__
