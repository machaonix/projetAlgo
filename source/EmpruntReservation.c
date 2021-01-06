#include "EmpruntReservation.h"

/*
    lireEmpruntReservation
Description :
  Lit les données d'un fichier pour les mettre dans un emprunt qui sera retourné.

Argument :
  FILE* flux -> flux du fichier à lire.
*/
EmpruntReservation lireEmpruntReservation(FILE* flux)
{
  EmpruntReservation er;
  fscanf(flux,"%u%u%u",&(er.id),&(er.idJeu),&(er.idEmprunter));
  er.date=lireDate(flux);
  return er;
}


/*
    afficherEmpruntReservation
Description :
  Affiche les données d'un emprunt dans un flux.

Argument :
  EmpruntReservation *er -> pointeur sur l'emprunt à afficher.
  FILE* flux -> flux de destination des données (stdout ou un fichier)
*/
void afficherEmpruntReservation(EmpruntReservation *er, FILE* flux)
{
  fprintf(flux,"%u\t%u\t%u\t\t",er->id,er->idJeu,er->idEmprunter);
  afficherDate(er->date,flux);
  fprintf(flux, "\n");
}
