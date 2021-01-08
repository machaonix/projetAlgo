#include "ListeEmpruntReservation.h"
#include "EmpruntReservation.h"


/*
    listeER_Vide
Description :
  Creer une liste vide.
*/
ListeER listeER_Vide(void) //Créer une nouvelle liste
{
  ListeER liste;
  liste=NULL;
  return liste;
}


/*
    listeER_estVide
Description :
  Vérifie si une liste est vide (TRUE si elle est vide, FALSE si elle ne l'est pas).

Arguments :
  listeER liste -> liste à vérifier.
*/
Bool listeER_estVide(ListeER liste)
{
  if(liste==NULL)
    return TRUE;
  return FALSE;
}


/*
    afficherListeEmpruntReservation
Description :
  Afficher une liste dans un flux.

Arguments :
  ListeER liste -> liste à afficher.
  FILE* flux -> flux de destination (stdout ou un fichier).
  int nb -> nombre d'élement dans la liste, inscrit au début d'un fichier. (n'est pas affiché sur stdout)
*/
void afficherListeEmpruntReservation(ListeER liste, FILE* flux,int nb)
{
  if(flux==stdout)
  {
      printf("Id\tIdJeu\tIdAdherant\tDate\n");
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


/*
    afficherListeERJeu
Description :
  Affiche les élément d'une liste qui concerne un jeu (passé par idJeu).

Arguments :
  ListeER liste -> liste dans laquelle sont les éléments à afficher.
  unsigned int idJeu -> identifiant du jeu dont on souhaite voir les emprunts ou reservations
*/
void afficherListeERJeu(ListeER liste, unsigned int idJeu)
{
  printf("Id\tIdJeu\tIdAdherant\tDate\n");

  while(liste!=NULL)
  {
    if(idJeu==(liste->empRes).idJeu)
      afficherEmpruntReservation(&(liste->empRes),stdout);
    liste=liste->suiv;
  }
}


/*
    chargerListeEmpruntReservation
Description :
  Charge une liste avec le contenu d'un fichier.

Arguments :
  char nomDeFichier[] -> chemin (relatif) du fichier à charger.
  int *nb -> pointeur sur le nombre d'élément dans le fichier.
*/
ListeER chargerListeEmpruntReservation(char nomDeFichier[], unsigned int *nb)
{
  ListeER liste=listeER_Vide(),origin=listeER_Vide();  //liste permettra de naviger dans la liste pour la création de la liste, origin est le pointeur sur le premier element de la
  FILE *flux;
  unsigned int i;
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
    fscanf(flux,"%u%u%u",&(liste->empRes.id),&(liste->empRes.idJeu),&(liste->empRes.idAdherant));
    liste->empRes.date=lireDate(flux);
    liste->suiv=NULL;
  }
  for(i=2;i<=(*nb);i++)
  {
    liste->suiv=(ListeER)malloc(sizeof(Element));
    liste=liste->suiv;
    fscanf(flux,"%u%u%u",&(liste->empRes.id),&(liste->empRes.idJeu),&(liste->empRes.idAdherant));
    liste->empRes.date=lireDate(flux);
    liste->suiv=NULL;
  }
  fclose(flux);
  return origin;
}

/*
    rechercherIdLibre
Description :
  Rechercher le premier identifiant inutilisé dans la liste. Pour garder une liste trié par identifiant des emprunts/reservations.

Arguments :
  ListeER liste -> liste dans laquelle chercher un identifiant libre.
*/
unsigned int rechercherIdLibre(ListeER liste)
{
  unsigned int x=0;
  while(liste!=NULL)
  {
    if(liste->empRes.id!=x)
      break;
    x+=1;
    liste=liste->suiv;
  }
  return x;
}


/*
    insererDevantEmpruntReservation
Description :
   Insère un élément au début de la liste.

Arguments :
  ListeER liste -> liste dans laquelle on insère l'élément.
  Emprunt er -> élément qu'on insère.
*/
ListeER insererDevantEmpruntReservation(ListeER liste, EmpruntReservation er)
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


/*
    insererEmpruntReservation
Description :
  Insère un emprunt ou une reservation dans une liste.

Arguments :
  ListeER liste -> liste dans laquelle on insère l'élément.
  int *nb -> pointeur sur le nombre d'élément dans la liste.
  EmpruntReservation er -> emprunt ou reservation à insérer (id compris dans er)
*/
ListeER insererEmpruntReservation(ListeER liste, unsigned int *nb, EmpruntReservation er)
{
  if(liste!=NULL)
    if (liste->empRes.id<er.id)
    {
      liste->suiv=insererEmpruntReservation(liste->suiv, nb, er);
      return liste;
    }

  liste=insererDevantEmpruntReservation(liste,er);
  *nb+=1;

  printf("\nId/reservation insérer avec l'Id: %u\n\n",er.id);
  return liste;
}


/*
    supprimerDevantEmpruntReservation
Description :
  Supprimer le premier élément d'une liste.

Arguments :
  ListeER liste -> liste dans laquelle on supprime l'élément.
*/
ListeER supprimerDevantEmpruntReservation(ListeER liste)
{
  ListeER elem;
  elem=liste;
  liste=liste->suiv;
  free(elem);
  return liste;
}


/*
    supprimerEmpruntReservation
Description :
  Supprime un emprunt ou une reservation donné d'une liste.

Arguments :
  ListeER liste -> liste dans laquelle on supprime l'élément.
  unsigned int id -> identifiant de l'emprunt ou de la reservation à supprimer.
  int *nb -> pointeur sur le nombre d'élément dans la liste.
*/
ListeER supprimerEmpruntReservation(ListeER liste, unsigned int id, unsigned int *nb, CodeErreur* cErr)
{
  ListeER origin=listeER_Vide();
  origin=liste;

  cErr = ERR_NO_ERR;

  if(origin==NULL)
  {
    fprintf(stderr, "Erreur %d: Emprunt/Reservation non trouvé\n",ERR_NOT_FOUND);
    *cErr = ERR_NOT_FOUND;
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
  *cErr = ERR_NOT_FOUND;
  return origin;
}


/*
    supprimerListe
Description :
  Supprime une liste entière.

Arguments :
  ListeER liste -> liste à supprimer.
*/
ListeER supprimerListe(ListeER liste)
{
  if(liste==NULL)
    return NULL;
  liste=supprimerListe(liste->suiv);
  free(liste);
  return NULL;
}


/*
    sauvegarder
Description :
  Sauvegarde une liste dans un fichier.

Arguments :
  ListeER liste -> liste à supprimer.
  char nomDeFichier[] -> chemin (relatif) du fichier dans lequelle sauvegarder la liste.
  int nb -> nombre d'élémement dans la liste.
*/
CodeErreur sauvegarderListeER(ListeER liste, char nomDeFichier[],int nb)
{
  FILE *flux;
  flux=fopen(nomDeFichier,"w");
  if(flux==NULL)
  {
    fprintf(stderr, "Erreur %d: Problème d'ouverture du fichier %s\n",ERR_OUVERTURE_FICHIER,nomDeFichier);
    return ERR_OUVERTURE_FICHIER;
  }
  afficherListeEmpruntReservation(liste,flux,nb);
  fclose(flux);
  return ERR_NO_ERR;
}


/*
    rechercherERListe_AdJeu
Description :
  Recherche un élément dans la liste selon idAdherant et idJeu et retourne l'id de l'élément.

Arguments :
  ListeER liste -> liste dans laquel on cherche l'élément.
  unsigned int idAdherant -> identifiant de l'adherant contenu dans l'élément à rechercher.
  unsigned int idJeu -> identifiant du jeu contenu dans l'élément à rechercher.
  Bool* trouve -> pointeur vers une variable pour indiquer si l'élément a été trouvé ou non.
*/
unsigned int rechercherListeER_AdJeu(ListeER liste, unsigned int idAdherant, unsigned int idJeu, Bool* trouve)
{
  while(liste!=NULL)
  {
    if(liste->empRes.idAdherant==idAdherant && liste->empRes.idJeu == idJeu)
    {
      *trouve=TRUE;
      return liste->empRes.id;
    }
    liste = liste->suiv;
  }
  *trouve=FALSE;
  return 0;
}


/*
    rechercherERListe_Jeu
Description :
  Recherche un élément dans la liste selon idJeu et retourne l'id de l'élément.

Arguments :
  ListeER liste -> liste dans laquel on cherche l'élément.
  unsigned int idJeu -> identifiant du jeu contenu dans l'élément à rechercher.
  Bool* trouve -> pointeur vers une variable pour indiquer si l'élément a été trouvé ou non.
*/
unsigned int rechercherListeER_Jeu(ListeER liste, unsigned int idJeu, Bool* trouve)
{
    while(liste!=NULL)
    {
      if(liste->empRes.idJeu == idJeu)
      {
        *trouve=TRUE;
        return liste->empRes.id;
      }
      liste = liste->suiv;
    }
    *trouve=FALSE;
    return 0;
}
