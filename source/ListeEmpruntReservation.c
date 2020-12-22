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

ListeER chargerListeEmprunReservation(char nomDeFichier[])
{
  Liste liste;
  Element *lsuiv;
  FILE *flux;
  flux=fopen(nomDeFichier,"r");
  if(flux==NULL)
  {
    fprintf(stderr, "Erreur %d: Problème d'ouverture du fichier %s\n",ERR_OUVERTURE_FICHIER,nomDeFichier);
    return ERR_OUVERTURE_FICHIER;
  }

  liste=chargercreerMaillon(flux);

  fclose(flux);
  return liste;
}

*Element chargercreerMaillon(FILE *flux)
{
  Element *elem;
  elem=(Element *)malloc(sizeof(Element));
  if(elem==NULL)
  {
    fprintf(stderr, "Erreur %d: Erreur de malloc\n",ERR_ALLOCATION);
    return ERR_ALLOCATION;
  }

  fscanf("%d%d%d",&(elem->empRes.id),&(elem->empRes.idJeu),&(elem->empRes.idEmprunter));
  elem->empResdate=lireDate(flux)
  if(!feof(flux))
    elem->suiv=chargercreerMaillon(flux);

  return elem;
}
