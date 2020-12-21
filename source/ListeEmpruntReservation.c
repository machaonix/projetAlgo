#include "listeEmpruntReservation.h"
#include "EmpruntReservation.h"

ListeER listeER_Vide(void) //Créer une nouvelle liste
{
  ListeER liste;
  return liste;
}

Bool listeER_estVide(ListeER liste)
{
  if(liste==NULL)
    return TRUE;
  return FALSE;
}

void afficherListeEmpruntReservation(ListeER liste, FILE* flux)
{
  if(flux==STDOUT)
  {
      printf("Id\tIdJeu\tIdAdherant\tDate d'emprunt\n");
  }

  while(listeER_estVide(liste)!=TRUE)
  {
    afficherEmpruntReservation(&(liste->empRes),flux);
    liste=liste->suiv;
  }
}

void afficherListeERJeu(ListeER liste, unsigned int idJeu)
{
  printf("Id\tIdJeu\tIdAdherant\tDate d'emprunt\n");

  while(listeER_estVide(liste)!=TRUE)
  {
    if(idJeu==(liste->empRes).idJeu)
      afficherEmpruntReservation(&(liste->empRes),STDOUT);
    liste=liste->suiv;
  }
}
