#ifndef _EmpruntReservation_H_
#define _EmpruntReservation_H_

#include <stdio.h>
#include "Date.h"
#include "CodeErreur.h"

typedef struct
{
    unsigned int id;
    unsigned int idEmprunter;//reference à une instance d'adherant
    unsigned int idJeu;//reference à une instance de jeu
    Date date;
} Emprunt, Reservation, EmpruntReservation;
//Pour les fonction communes EmpruntReservation sera utilise

EmpruntReservation lireEmpruntReservation(FILE* flux);
void afficherEmpruntReservation(EmpruntReservation *Empruntreservation, FILE* flux);
// *EmpruntReservation -> pointeur sur une structure pour que ça soit moins lourd

//interactif
EmpruntReservation nouvEmpruntReservation(unsigned int id);

#endif //_EmpruntReservation_H_
