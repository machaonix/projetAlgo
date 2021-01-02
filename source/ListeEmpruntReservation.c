#include "ListeEmpruntReservation.h"
#include "EmpruntReservation.h"

ListeER listeER_Vide(void) //Créer une nouvelle liste
{
  ListeER liste;
  liste=NULL;
  return liste;
}

Bool listeER_estVide(ListeER liste)
{
  if(liste==NULL)
    return TRUE;
  return FALSE;
}

void afficherListeEmpruntReservation(ListeER liste, FILE* flux,int nb)
{
  if(flux==stdout)
  {
      printf("Id\tIdJeu\tIdEmprunter\tDate d'emprunt\n");
  } else
  {
    fprintf(flux,"%d\n",nb);
  }
  while(listeER_estVide(liste)!=TRUE)
  {
    afficherEmpruntReservation(&(liste->empRes),flux);
    liste=liste->suiv;
  }
}

void afficherListeERJeu(ListeER liste, unsigned int idJeu)
{
  printf("Id\tIdJeu\tIdEmprunter\tDate d'emprunt/de reservation\n");

  while(liste!=NULL)
  {
    if(idJeu==(liste->empRes).idJeu)
      afficherEmpruntReservation(&(liste->empRes),stdout);
    liste=liste->suiv;
  }
}

ListeER chargerListeEmpruntReservation(char nomDeFichier[],int *nb)
{
  ListeER liste=listeER_Vide(),origin=listeER_Vide();  //liste permettra de naviger dans la liste pour la création de la liste, origin est le pointeur sur le premier element de la
  FILE *flux;
  int i;
  flux=fopen(nomDeFichier,"r");
  if(flux==NULL)
  {
    fprintf(stderr, "Erreur %d: Problème d'ouverture du fichier %s\n",ERR_OUVERTURE_FICHIER,nomDeFichier);
    return NULL;
  }

  fscanf(flux,"%d",nb);
  if(*nb>0)
  {
    liste=(ListeER)malloc(sizeof(Element));
    origin=liste;
    fscanf(flux,"%u%u%u",&(liste->empRes.id),&(liste->empRes.idJeu),&(liste->empRes.idEmprunter));
    liste->empRes.date=lireDate(flux);
    liste->suiv=NULL;
  }
  for(i=2;i<=(*nb);i++)
  {
    liste->suiv=(ListeER)malloc(sizeof(Element));
    liste=liste->suiv;
    fscanf(flux,"%u%u%u",&(liste->empRes.id),&(liste->empRes.idJeu),&(liste->empRes.idEmprunter));
    liste->empRes.date=lireDate(flux);
    liste->suiv=NULL;
  }
  fclose(flux);
  return origin;
}

Element* rechercherListeEmpruntReservation(ListeER liste, unsigned int id) //retourne l'adresse d'un emprunt ou d'une reservation données par id
{
  while(liste!=NULL && liste->empRes.id<=id)
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

unsigned int rechercherIdLibre(ListeER liste)
{
  unsigned int x=0;
  while(liste->empRes.id==x)
  {
    x+=1;
    if(liste->suiv==NULL)
      break;
    liste=liste->suiv;
  }
  return x;
}

ListeER insererDevantEmpruntReservation(ListeER liste, Emprunt er)
{
  Element *elem;
  elem=(Element *)malloc(sizeof(Element));
  if(elem==NULL)
  {
    fprintf(stderr, "Erreur %d: Erreur de malloc\n",ERR_ALLOCATION);
    return liste;
  }

  elem->empRes=er;
  elem->suiv=liste;
  return elem;
}

ListeER insererEmpruntReservation(ListeER liste, int *nb, TableauJeu* tabJeu)
{
  unsigned int id; //Premier Id libre dans la liste;
  Bool jeu_libre;
  Emprunt er;

  if(liste!=NULL)
    if(liste->empRes.id==id)
    {
      fprintf(stderr, "Erreur %d: l'id %u existe déjà\n",ERR_EXISTE_DEJA,id);
      return liste;
    } else if (liste->empRes.id<id)
    {
      liste->suiv=insererEmpruntReservation(liste->suiv,id,nb);
      return liste;
    }

  id_libre=rechercherIdLibre(libre);

  er=nouvEmpruntReservation(id);
  if(jeuDisponible(tabJeu,er.id)==FALSE)
  {
    fprinf("Erreur %d: il n'y a plus d'exemplaire disponible\n",ERR_OPERATION_INVALIDE);
  }
  liste=insererDevantEmpruntReservation(liste,er);
  *nb+=1;

  printf("\nId/reservation insérer avec l'Id: %u\n\n",id);
  return liste;
}

ListeER supprimerDevantEmpruntReservation(ListeER liste)
{
  ListeER elem;
  elem=liste;
  liste=liste->suiv;
  free(elem);
  return liste;
}

ListeER supprimerEmpruntReservation(ListeER liste, unsigned int id, int *nb)
{
  ListeER origin=listeER_Vide();
  origin=liste;
  if(origin==NULL)
  {
    fprintf(stderr, "Erreur %d: Emprunt/Reservation non trouvé\n",ERR_NOT_FOUND);
    return origin;
  }
  if(liste->empRes.id==id)
  {
    origin=supprimerDevantEmpruntReservation(origin);
    *nb-=1;
    return origin;
  }
  while(liste->suiv!=NULL)
  {
    if(liste->suiv->empRes.id==id)
    {
      liste->suiv=supprimerDevantEmpruntReservation(liste->suiv);
      *nb-=1;
      return origin;
    }
    liste=liste->suiv;
  }
  if(liste->empRes.id==id)
  {
    liste=supprimerDevantEmpruntReservation(liste);
    *nb-=1;
  }
  fprintf(stderr, "Erreur %d: Emprunt/Reservation non trouvé\n",ERR_NOT_FOUND);
  return origin;
}

ListeER supprimerListe(ListeER liste)
{
  if(liste==NULL)
    return NULL;
  liste=supprimerListe(liste->suiv);
  free(liste);
  return NULL;
}

void sauvegarder(ListeER liste, char nomDeFichier[],int nb)
{
  FILE *flux;
  flux=fopen(nomDeFichier,"w");
  if(flux==NULL)
  {
    fprintf(stderr, "Erreur %d: Problème d'ouverture du fichier %s\n",ERR_OUVERTURE_FICHIER,nomDeFichier);
    exit(ERR_OUVERTURE_FICHIER);
  }
  afficherListeEmpruntReservation(liste,flux,nb);
}
