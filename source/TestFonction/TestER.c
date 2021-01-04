#include "TestER.h"

void testER()
{
  int nb_Emprunt,nb_Reservation,id_libre;
  ListeER liste_Emprunt=listeER_Vide(),liste_Reservation=listeER_Vide();

  liste_Emprunt=chargerListeEmpruntReservation("donnee/emprunts.don",&nb_Emprunt);
  liste_Reservation=chargerListeEmpruntReservation("donnee/reservations.don",&nb_Reservation);

  //afficherListeEmpruntReservation(liste_Reservation, stdout,nb_Reservation);
  printf("\n");

  afficherListeERJeu(liste_Reservation,0);

  liste_Emprunt=supprimerListe(liste_Emprunt);
  liste_Reservation=supprimerListe(liste_Reservation);
}
