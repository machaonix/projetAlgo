#include "EmpruntReservation.h"

EmpruntReservation lireEmpruntReservation(FILE* flux)
{
  EmpruntReservation er;
  fscanf(flux,"%u%u%u",&(er.id),&(er.idJeu),&(er.idEmprunter));
  er.date=lireDate(flux);
  return er;
}

void afficherEmpruntReservation(EmpruntReservation *er, FILE* flux)
{
  fprintf(flux,"%u\t%u\t%u\t\t",er->id,er->idJeu,er->idEmprunter);
  afficherDate(er->date,flux);
  fprintf(flux, "\n");
}

//interactif
EmpruntReservation nouvEmpruntReservation(unsigned int id)
{
  EmpruntReservation er;
  er.id=id;
  printf("Quel est l'identifiant du jeu emprunté/reservé: ");
  scanf("%d",&(er.idJeu));

  printf("Quel est l'identifiant du membre: ");
  scanf("%d",&(er.idEmprunter));

  printf("Quel est la date d'emprunt: ");
  er.date=lireDate(stdin);

  return er;
}
