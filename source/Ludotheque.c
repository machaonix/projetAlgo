#include "Ludotheque.h"


void afficheMenu(void)
{	
	printf("\n\tMenu :\n");
	printf("%d)\tReserver un jeu\n", CHOIX_RESERVER);
	printf("%d)\tAnnuler une reservation\n", CHOIX_ANNULER_RESERVATION);
	printf("%d)\tEmprunter un jeu\n", CHOIX_EMPRUNTER);
	printf("%d)\tRetour jeu\n", CHOIX_RETOUR_JEU);
	printf("%d)\tAfficher liste des jeux\n", CHOIX_AFFICHE_JEU);
	printf("%d)\tTrier les jeux\n", CHOIX_TRIER_JEU);
	printf("%d)\tNouvel adherant\n", CHOIX_NOUV_ADHERANT);
	printf("%d)\tRenouveler un abonement\n", CHOIX_RENOUV_ADHERANT);
	printf("%d)\tAfficher liste des adherants\n", CHOIX_AFFICHE_ADHERANT);
	printf("%d)\tAfficher liste des emprunts en cours\n", CHOIX_AFFICHE_EMPRUNT);
	printf("%d)\tAfficher liste des reservations en cours\n", CHOIX_AFFICHE_RESERVATION);
	printf("%d)\tAfficher la liste des reservations pour un jeu\n", CHOIX_AFFICHE_RESERVATION_JEU);
	printf("%d)\tSauvegarder\n", CHOIX_SAUVEGARDER);
	printf("%d)\tQuitter\n", CHOIX_QUITTER);
}

void Ludotheque(void)
{
	TableauJeu tabJeu;
	Adherant *tAdherant;
	unsigned int tMaxAdherant = 5;
	int nbElemAdhearant;
	ListeER liste_Emprunt=listeER_Vide(),liste_Reservation=listeER_Vide();
	unsigned int nb_Emprunt,nb_Reservation;
	unsigned int reponceDuMenu;
	Bool lance = TRUE;
	CodeErreur cErr;
	
	fprintf(stderr, "\n1\n");fflush(stderr);
	//initialisation et chargement
	initTabJeu(&tabJeu);
 	cErr = chargerTabJeu(&tabJeu, "donnee/jeux.don");
 	if (cErr != ERR_NO_ERR) return;
	fprintf(stderr, "\n1 Jeux ok\n");fflush(stderr);

	tAdherant = (Adherant*) malloc(sizeof(Adherant)*tMaxAdherant);
	nbElemAdhearant = chargerLesAdherants(&tAdherant, &tMaxAdherant, "donnee/adherant.don");
	if(nbElemAdhearant < 0) return;
	fprintf(stderr, "\n1 Adherant ok\n");fflush(stderr);
	
	liste_Emprunt=chargerListeEmpruntReservation("donnee/emprunts.don",&nb_Emprunt);
	fprintf(stderr, "\n1 Emprunt ok\n");fflush(stderr);
  	liste_Reservation=chargerListeEmpruntReservation("donnee/reservations.don",&nb_Reservation);
	fprintf(stderr, "\n1 reservations ok\n");fflush(stderr);
	
	fprintf(stderr, "\n2\n");fflush(stderr);
	//Menu
	while(lance)
	{
		afficheMenu();
		printf("\n>>>"); 
		fflush(stdout);
		scanf("%u%*c", &reponceDuMenu);

		switch(reponceDuMenu)
		{
			case CHOIX_RESERVER:
				GLOBAL_Reserver(&liste_Reservation, &nb_Reservation, &tabJeu, tAdherant, &nbElemAdhearant, &tMaxAdherant);
				break;
			case CHOIX_ANNULER_RESERVATION://////////////////////////////////////////////////////////
				break;
			case CHOIX_EMPRUNTER://////////////////////////////////////////////////////////
				break;
			case CHOIX_RETOUR_JEU://////////////////////////////////////////////////////////
				break;
			case CHOIX_AFFICHE_JEU:
				afficheTabJeu(&tabJeu, stdout);
				break;
			case CHOIX_TRIER_JEU:
				triTabJeuInteractif(&tabJeu);
				break;
			case CHOIX_NOUV_ADHERANT:
				GLOBAL_NouvelAdherant(tAdherant, &nbElemAdhearant, &tMaxAdherant);
				break;
			case CHOIX_RENOUV_ADHERANT:
				GLOBAL_RenouvellerAdherant(tAdherant, nbElemAdhearant);
				break;
			case CHOIX_AFFICHE_ADHERANT:
				afficheTabAdherant(tAdherant, nbElemAdhearant, stdout, TRUE);
				break;
			case CHOIX_AFFICHE_EMPRUNT:
				afficherListeEmpruntReservation(liste_Emprunt, stdout, nb_Emprunt);
				break;
			case CHOIX_AFFICHE_RESERVATION:
				afficherListeEmpruntReservation(liste_Reservation, stdout, nb_Reservation);
				break;
			case CHOIX_AFFICHE_RESERVATION_JEU:
				GLOBAL_afficherListeERJeu_Interactif(liste_Reservation, &tabJeu, TRUE);
				break;
			case CHOIX_AFFICHE_EMPRUNT_JEU:
				GLOBAL_afficherListeERJeu_Interactif(liste_Emprunt, &tabJeu, FALSE);
				break;
			case CHOIX_SAUVEGARDER:
				GLOBAL_Sauvegarder(&tabJeu, tAdherant, nbElemAdhearant, liste_Reservation, nb_Reservation, liste_Emprunt, nb_Emprunt);
				break;
			case CHOIX_QUITTER:
				if (UTILE_Choix_O_N("Souhaitez vous sauvegarder avant de quitter"))
					GLOBAL_Sauvegarder(&tabJeu, tAdherant, nbElemAdhearant, liste_Reservation, nb_Reservation, liste_Emprunt, nb_Emprunt);
				lance = FALSE;
				break;
			default:
				printf("Instruction Invalide\n");
				break;
			
		}
	}


	supprimerListe(liste_Reservation);
	supprimerListe(liste_Emprunt);
	libererTabJeu(&tabJeu);
	free(tAdherant);

}


Bool GLOBAL_Reserver(ListeReservation* liste_Reservation, unsigned int* nb_Reservation, TableauJeu* tabJeu, Adherant tAdherant[], int* nbElemAdhearant, unsigned int* tMaxAdherant)
{
	Reservation reservation;
	Bool trouve;
	unsigned int rangAdherant;



	printf("Quel est l'identifiant de l'adherant: ");
	fflush(stdout);
  	scanf("%u%*c",&(reservation.idEmprunter));

  	rangAdherant = rechercherUnAdherant(tAdherant, *nbElemAdhearant, reservation.idEmprunter, &trouve);
  	if (trouve == FALSE)
  	{
  		if(UTILE_Choix_O_N("Identifiant d'adherant non attribué, souhaitez vous créer un nouvel adherant"))
  		{
  			if(!GLOBAL_NouvelAdherant(tAdherant, nbElemAdhearant, tMaxAdherant))
  			{
  				printf("Reservation avortée\n");
  				return FALSE;
  			}
  		}
  	}

  	printf("Saisir la date du jour (JJ/MM/YYYY):\n");
  	fflush(stdout);
	reservation.date = lireDate(stdin);

  	if (checkInscriptionValide(&(tAdherant[rangAdherant]), &reservation.date) == FALSE)
  	{
  		if(UTILE_Choix_O_N("Cet adherant n'a plus une insciption valide, voulez vous renouveller son abonement"))
  		{
  			if(!GLOBAL_RenouvellerAdherant(tAdherant, *nbElemAdhearant))
  			{
  				printf("Reservation avortée\n");
  				return FALSE;
  			}
  		}
  	}


	printf("Quel est l'identifiant du jeu à reserver: ");
	fflush(stdout);
  	scanf("%u%*c",&(reservation.idJeu));

	printf("Id jeu entre");
	fflush(stdout);
	rechercherIdJeu(tabJeu, reservation.idJeu, &trouve);
  	if (trouve == FALSE)
  	{
  		printf("Cette identifiant de jeu n'est pas attribué\n");
  		printf("Reservation avortée\n");
  		return FALSE;
  	}

	printf("Id jeu entre");
	fflush(stdout);

  	reservation.id = rechercherIdLibre(*liste_Reservation);

	printf("Id jeu entre");
	fflush(stdout);

	*liste_Reservation = insererEmpruntReservation(*liste_Reservation, nb_Reservation, reservation);
	afficherListeEmpruntReservation(*liste_Reservation, stdout, *nb_Reservation);

	printf("Id jeu entre");
	fflush(stdout);

	return TRUE;
}


Bool GLOBAL_NouvelAdherant(Adherant tAdherant[], int* nbElemAdhearant, unsigned int* tMaxAdherant)
{
	Adherant adherantTmp;

	adherantTmp = nouvAdherant(tAdherant[*nbElemAdhearant-1].id+1);
	*nbElemAdhearant = insererAdherant(&tAdherant, *nbElemAdhearant, tMaxAdherant, &adherantTmp);
	if(*nbElemAdhearant >= 0)
	{
		printf("Nouvel adherant enregistrer avec succès\n");
		return TRUE;
	}
	else
	{
		printf("Une erreur a eu lieux lors de l'enregistrement : %d\n", *nbElemAdhearant);
		return FALSE;
	}	
}

Bool GLOBAL_RenouvellerAdherant(Adherant tAdherant[], unsigned int nbElemAdhearant)
{
	unsigned int idAdherantTmp, indexAdherant;
	float montantRemis;
	Date dateTmp;
	Bool trouveAdherant;


	printf("Saisir l'ID d'un adherant\n>>>"); 
	fflush(stdout);
	scanf("%u%*c", &idAdherantTmp);
	indexAdherant = rechercherUnAdherant(tAdherant, nbElemAdhearant, idAdherantTmp, &trouveAdherant);
	printf("Montant remis\n>>>"); 
	fflush(stdout);
	scanf("%f%*c", &montantRemis);
	if(montantRemis < PRIX_ADHERANT)
	{
		printf("Le montant remis n'est pas sufissant, il manque %.2f€ (prix : %.2f€)", PRIX_ADHERANT-montantRemis, PRIX_ADHERANT);
		return FALSE;
	}

	printf("Saisir la date du jour (JJ/MM/YYYY):\n");
	fflush(stdout);
	dateTmp = lireDate(stdin);
	
	renouvelerInscription(&(tAdherant[indexAdherant]), &dateTmp);

	return TRUE;
}

void GLOBAL_Sauvegarder(TableauJeu* tabJeu, Adherant tAdherant[], unsigned int nbElemAdhearant, ListeReservation liste_Reservation, int nb_Reservation, ListeEmprunt liste_Emprunt, int nb_Emprunt)
{
	printf("Sauvegarde\n");
	sauvegarderTabJeu(tabJeu, "donnee/jeux.don");
	sauvegarderAdherant(tAdherant, nbElemAdhearant, "donnee/adherant.don");
	sauvegarderListeER(liste_Emprunt, "donnee/emprunts.don", nb_Emprunt);
	sauvegarderListeER(liste_Reservation, "donnee/reservations.don", nb_Reservation);
}

void GLOBAL_afficherListeERJeu_Interactif(ListeER liste, TableauJeu* tabJeu, Bool isReservation)
{
	unsigned int idJeu;
	Bool trouve;
	printf("Quel est l'identifiant du jeu pour lequel vous voulez afficher les ");
	if (isReservation)
		printf("reservations : ");
	else
		printf("emprunts : ");		
	scanf("%u", &idJeu);

	rechercherIdJeu(tabJeu, idJeu, &trouve);

	if (trouve == FALSE)
	{
		printf("Le jeu d'id %u n'existe pas.\n", idJeu);
		return;
	}
	afficherListeERJeu(liste, idJeu);
}



Bool UTILE_Choix_O_N(char message[])
{
	char choix;
	printf("%s (O/N) ? : ", message);
	fflush(stdout);
	scanf("%c%*c", &choix);
	while (choix != 'O' && choix != 'N')
	{
		printf("Veuillez par O ou par N : ");
		fflush(stdout);
		scanf("%c%*c", &choix);
	}
	if (choix == 'O')
		return TRUE;
	return FALSE;
}

