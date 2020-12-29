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

Element* chargercreerMaillon(FILE *flux)
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

ListeER rechercherListeEmpruntReservation(ListeER liste, unsigned int id) //retourne l'adresse d'un emprunt ou d'une reservation données par id
{
  while(liste->suiv!=NULL)
  {
    if(liste->empRes.id==id)
    {
      return liste;
    }
    liste=liste->suiv;
  }
    fprintf(stderr, "Erreur %d: Emprunt/Reservation non trouvé\n",ERR_NOT_FOUND);
    return NULL;
}

ListeER insererDevantEmpruntReservation(ListeER liste, Emprunt er)
{
  Element *elem;
  elem=(Element *)malloc(sizeof(Element));
  if(elem==NULL)
  {
    fprintf(stderr, "Erreur %d: Erreur de malloc\n",ERR_ALLOCATION);
    return ERR_ALLOCATION;
  }

  elem->empRes=er;
  elem->suiv=liste;
  return elem;
}

ListeER insererEmpruntReservation(listeER liste, unsigned int id)
{
  Emprunt er;
  if(liste->empRes.id==id)
  {
    fprintf(stderr, "Erreur %d: l'id %d existe déjà\n",ERR_EXISTE_DEJA,id);
    return liste;
  } else if (liste->empRes.id<id)
    liste->suiv=insererEmpruntReservation(liste->suiv,id);
  er=nouvEmpruntReservation(id);
  liste=insererDevantEmpruntReservation(liste,er);
  return liste;
}

ListeER supprimerDevantEmpruntReservation(ListeER liste)
{
  Element *elem
  elem = liste;
  liste=liste->suiv;
  free(elem);
  return liste;
}

listeER supprimerEmpruntReservation(listeER liste, unsigned int id)
{
  if(liste->empRes.id==id)
  {
    liste=supprimerDevantEmpruntReservation(liste);
    return liste;
  } else if (liste->empRes.id==NULL)
  {
    fprintf(stderr,"Erreur %d: Id introuvable\n",ERR_NOT_FOUND);
    return liste;
  }
  liste->suiv=supprimerEmpruntReservation(liste->suiv,id);
  return liste;
}

ListeER supprimerListe(listeER liste)
{
  if(liste==NULL)
    return NULL;
  liste=supprimerListe(liste->suiv);
  free(liste);
  return NULL;
}
