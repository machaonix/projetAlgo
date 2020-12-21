#include "EmpruntReservation.h"

EmpruntReservation lireEmpruntReservation(FILE* flux)
{
  EmpruntReservation er;
  fscanf(flux,"%d%d%d",&(er.id),&(er.idJeu),&(er.idAdherant));
  er.date=lireDate(flux);
  return er;
}

void afficherEmpruntReservation(EmpruntReservation *Empruntreservation, FILE* flux)
{
  fprintf(flux,"%d\t%d\t%d\t",er->id),er->idJeu),er->idAdherant);
  afficherDate(er->date,flux);
  fprintf(flux, "\n");
}

//interactif
EmpruntReservation nouvEmpruntReservation(unsigned int id)
{
  EmpruntReservation er;
  printf("Quel est l'identifiant du jeu emprunté: ");
  scanf("%d",&(er.id));

  printf("Quel est l'identifiant du membre: ");
  scanf("%d",&(er.idEmprunter));

  printf("Quel est l'identifiant du jeu emprunté: ");
  scanf("%d/%d/%d",&(er.date));

  return er;
}
