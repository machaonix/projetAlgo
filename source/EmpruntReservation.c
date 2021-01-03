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


/*
    nouvEmpruntReservation
Description :
  Créer un emprunt ou une reservation, en demandant les informations de l'emprunt à l'utilisateur.

Arguments :
  unsigned int id -> identifiant de l'emprunt ou de la reservation
*/
/*EmpruntReservation nouvEmpruntReservation(unsigned int id)
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
}*/
