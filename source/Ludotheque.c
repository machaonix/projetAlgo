#include "Ludotheque.h"


void afficheMenu(void)
{
	printf("\n\tMenu :\n");
	printf("%d)\tAnnuler une reservation\n", CHOIX_ANNULER_RESERVATION);
	printf("%d)\tEmprunter un jeu\n", CHOIX_EMPRUNTER);
	printf("%d)\tRetour jeu\n", CHOIX_RETOUR_JEU);
	printf("%d)\tAfficher liste des jeux\n", CHOIX_AFFICHE_JEU);
	printf("%d)\tTrier les jeux\n", CHOIX_TRIER_JEU);
	printf("%d)\tAjouter un jeux\n", CHOIX_AJOUTER_JEU);
	printf("%d)\tModifier ou supprimer un jeu\n", CHOIX_MODIFIER_SUPPRIMER_JEU);
	printf("%d)\tNouvel adherant\n", CHOIX_NOUV_ADHERANT);
	printf("%d)\tRenouveler un abonement\n", CHOIX_RENOUV_ADHERANT);
	printf("%d)\tAfficher liste des adherants\n", CHOIX_AFFICHE_ADHERANT);
	printf("%d)\tAfficher liste des emprunts en cours\n", CHOIX_AFFICHE_EMPRUNT);
	printf("%d)\tAfficher liste des reservations en cours\n", CHOIX_AFFICHE_RESERVATION);
	printf("%d)\tAfficher la liste des reservations pour un jeu\n", CHOIX_AFFICHE_RESERVATION_JEU);
	printf("%d)\tAfficher la liste des emprunt pour un jeu\n", CHOIX_AFFICHE_EMPRUNT_JEU);
	printf("%d)\tSauvegarder\n", CHOIX_SAUVEGARDER);
	printf("%d)\tQuitter\n", CHOIX_QUITTER);
}

void Ludotheque(void)
{
	TableauJeu tabJeu;
	Adherant *tAdherant;
	unsigned int tMaxAdherant = 2;
	int nbElemAdhearant;
	ListeER liste_Emprunt=listeER_Vide(),liste_Reservation=listeER_Vide();
	unsigned int nb_Emprunt,nb_Reservation;
	unsigned int reponceDuMenu;
	Bool lance = TRUE;
	CodeErreur cErr;
	Date dateDuJour;

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

	UTILE_InitNbJeuDispo(liste_Emprunt,&tabJeu);
	fprintf(stderr, "\n2\n");fflush(stderr);

	printf("Saisir la date du jour (JJ/MM/YYYY):");
	fflush(stdout);
	dateDuJour = lireDate(stdin);
	//Menu
	while(lance)
	{
		afficheMenu();
		printf("\n>>>");
		fflush(stdout);
		scanf("%u%*c", &reponceDuMenu);

		switch(reponceDuMenu)
		{
			case CHOIX_ANNULER_RESERVATION:
				 if(GLOBAL_Anuller_Reservation(&liste_Reservation, &nb_Reservation, tAdherant, nbElemAdhearant, &tabJeu))
				 	printf("Réservation annulé avec succès\n");
				break;
			case CHOIX_EMPRUNTER:
				GLOBAL_Emprunter(&liste_Reservation, &nb_Reservation, &liste_Emprunt, &nb_Emprunt, &tabJeu, &tAdherant, &nbElemAdhearant, &tMaxAdherant, dateDuJour);
				break;
			case CHOIX_RETOUR_JEU://////////////////////////////////////////////////////////
				break;
			case CHOIX_AFFICHE_JEU:
				afficheTabJeu(&tabJeu, stdout);
				break;
			case CHOIX_TRIER_JEU:
				triTabJeuInteractif(&tabJeu);
				break;
			case CHOIX_AJOUTER_JEU:
				cErr = ajouterJeuInteractif(&tabJeu);
				if (cErr != ERR_NO_ERR)
					printf("Erreur lors de l'ajout du jeu\n");
				break;
			case CHOIX_MODIFIER_SUPPRIMER_JEU:
				GLOBAL_ModifierSupprimerJeu(&tabJeu, &liste_Reservation, &nb_Reservation, liste_Emprunt);
				break;
			case CHOIX_NOUV_ADHERANT:
				GLOBAL_NouvelAdherant(&tAdherant, &nbElemAdhearant, &tMaxAdherant, NULL, dateDuJour);
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
				if (IO_Choix_O_N("Souhaitez vous sauvegarder avant de quitter"))
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

Bool GLOBAL_ModifierSupprimerJeu(TableauJeu* tabJeu, ListeReservation* liste_Reservation, unsigned int* nb_Reservation, ListeEmprunt liste_Emprunt)
{
	Bool trouve;
	unsigned int rangJeu;
	Jeu* jeu;
	unsigned int idER;
	CodeErreur cErr;

	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return FALSE;

	if (trouve == FALSE)
		return FALSE;

	jeu = tabJeu->jeux[rangJeu];

	idER = rechercherListeER_Jeu(liste_Emprunt, jeu->id, &trouve);
	if (trouve)
	{
		printf("Ce jeu est actuellement emprunter: notemment identifiant %u\n", idER);
  		printf("Operation avortée\n");
		return FALSE;
	}

	idER = rechercherListeER_Jeu(*liste_Reservation, jeu->id, &trouve);
	if (trouve)
	{
		printf("Ce jeu est actuellement reserver: notemment identifiant %u\n", idER);
		if (IO_Choix_O_N("Souhaiter vous annuler toutes ces reservations"))
		{
			while (trouve)
			{
				*liste_Reservation = supprimerEmpruntReservation(*liste_Reservation, idER, nb_Reservation, &cErr);
				if (cErr != ERR_NO_ERR)
				{
					fprintf(stderr, "Erreur lors de la suppression des reservations\n");
					return FALSE;
				}
				idER = rechercherListeER_Jeu(*liste_Reservation, jeu->id, &trouve);
			}
		}
		else
		{
	  		printf("Operation avortée\n");
			return FALSE;
		}
	}

	printf("\n");
	afficheJeu(jeu, stdout);
	if (IO_Choix_O_N("\nSouhaitez vous supprimer le jeu ci dessus"))
	{
		cErr = retirerJeu(tabJeu, jeu);
		if (cErr != ERR_NO_ERR)
		{
			fprintf(stderr, "Erreur lors de la suppression du jeu\n");
			return FALSE;
		}
		printf("Jeu supprimé\n");
		return TRUE;
	}

	return TRUE;
}


Bool GLOBAL_Anuller_Reservation(ListeReservation* lr, unsigned int* nb_Reservation, Adherant tAdherant[], unsigned int nbElemAdhearant, TableauJeu* tabJeu)
{
	unsigned int idAdherant, idReservation;
	unsigned int rangJeu;
	Jeu* jeuReserve;
	Bool trouve;
	CodeErreur cErr;

	printf("Entrez l'ID de l'adherant\n>>>"); scanf("%u%*c", &idAdherant);
	rechercherUnAdherant(tAdherant, nbElemAdhearant, idAdherant, &trouve);
	if(!trouve)
	{
		fprintf(stderr, "Cet adherant n'existe pas\n");
		return FALSE;
	}

	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return FALSE;

	if (trouve == FALSE)
		return FALSE;

	jeuReserve = tabJeu->jeux[rangJeu];

	idReservation = rechercherListeER_AdJeu(*lr, idAdherant, jeuReserve->id, &trouve);
	if(!trouve)
	{
		fprintf(stderr, "L'adherant %d n'as pas réservé le jeu %d\n", idAdherant, jeuReserve->id);
		return FALSE;
	}

	*lr = supprimerEmpruntReservation(*lr, idReservation, nb_Reservation, &cErr);
	if(cErr == ERR_NOT_FOUND)
	{
		fprintf(stderr, "Une erreur à eu lieu lors de l'annulation de la reservation\n");
		return FALSE;
	}
	return TRUE;
}

Bool GLOBAL_Emprunter(ListeReservation* liste_Reservation, unsigned int* nb_Reservation, ListeEmprunt* liste_Emprunt, unsigned int* nb_Emprunt, TableauJeu* tabJeu, Adherant* tAdherant[], int* nbElemAdhearant, unsigned int* tMaxAdherant, Date dateDuJour)
{
	EmpruntReservation er;

	ListeER** liste;
	unsigned int** nb_elem;

	Bool trouve;
	unsigned int rangAdherant;
	unsigned int rangJeu;
	Jeu* jeuAEmprunter;

	CodeErreur cErr;


	er.date = dateDuJour;


	if(IO_Choix_O_N("Est-ce un nouvel adherant"))
	{
		if(!GLOBAL_NouvelAdherant(tAdherant, nbElemAdhearant, tMaxAdherant, &rangAdherant, dateDuJour))
		{
			printf("Reservation avortée\n");
			return FALSE;
		}
		er.idAdherant = (*tAdherant)[rangAdherant].id;
	}
	else
	{
		printf("Quel est l'identifiant de l'adherant: ");
		fflush(stdout);
	  	scanf("%u%*c",&(er.idAdherant));

	  	rangAdherant = rechercherUnAdherant(*tAdherant, *nbElemAdhearant, er.idAdherant, &trouve);
	  	if (trouve == FALSE)
	  	{
	  		printf("Veuillez donner un id valable : ");
	  		fflush(stdout);
	  		scanf("%u%*c",&(er.idAdherant));

	  		rangAdherant = rechercherUnAdherant(*tAdherant, *nbElemAdhearant, er.idAdherant, &trouve);
	  	}

	  	if (checkInscriptionValide(&((*tAdherant)[rangAdherant]), &er.date) == FALSE)
	  	{
	  		if(IO_Choix_O_N("Cet adherant n'a plus une insciption valide, voulez vous renouveller son abonement"))
	  		{
	  			if(!GLOBAL_RenouvellerAdherant(*tAdherant, *nbElemAdhearant))
	  			{
	  				printf("Reservation avortée\n");
	  				return FALSE;
	  			}
	  		}
	  		else
	  		{
	  			printf("Reservation avortée\n");
	  			return FALSE;
	  		}
	  	}
	}
	//id adherant valable


	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return FALSE;

	if (trouve == FALSE)
		return FALSE;

	jeuAEmprunter = tabJeu->jeux[rangJeu];

  	if (jeuDisponible(tabJeu, jeuAEmprunter) == TRUE)
  	{
  		liste = &liste_Emprunt;
  		nb_elem = &nb_Emprunt;

  		jeuAEmprunter->nbExemplaireDispo -= 1;
  	}
  	else
  	{
  		if(IO_Choix_O_N("Jeu indisponible, voulez vous reserver"))
  		{
	  		liste = &liste_Reservation;
	  		nb_elem = &nb_Reservation;
  		}
  		else
  		{
	  		printf("Reservation avortée\n");
	  		return FALSE;
  		}
  	}

	//rechercher un emprunt avec l'id de l'adherant et et celui du jeu
	rechercherListeER_AdJeu(*liste_Emprunt,  er.idAdherant, jeuAEmprunter->id, &trouve);
	if (trouve)
	{
		printf("Cette adherant à déjà un emprunt en cours pour ce jeu\n");
	  	printf("Reservation avortée\n");
	  	return FALSE;
	}

	//rechercher une reseration avec l'id de l'adherant et et celui du jeu
	rechercherListeER_AdJeu(*liste_Reservation,  er.idAdherant, jeuAEmprunter->id, &trouve);
	if (trouve)
	{
		printf("Cette adherant à déjà reserver en cours pour ce jeu\n");
		printf("Reservation avortée\n");
		return FALSE;
	}

	er.idJeu =  jeuAEmprunter->id;
	er.id = rechercherIdLibre(**liste);

	**liste = insererEmpruntReservation(**liste, *nb_elem, er);

	return TRUE;
}


Bool GLOBAL_NouvelAdherant(Adherant* tAdherant[], int* nbElemAdhearant, unsigned int* tMaxAdherant, unsigned int* rangNouvAdherant, Date dateDuJour)
{
	Adherant adherantTmp;
	Bool trouve;

	adherantTmp = nouvAdherant(rechercherIDAdherantLibre(*tAdherant, *nbElemAdhearant), dateDuJour);
	*nbElemAdhearant = insererAdherant(tAdherant, *nbElemAdhearant, tMaxAdherant, &adherantTmp);
	if(*nbElemAdhearant >= 0)
	{
		if (rangNouvAdherant != NULL)
			*rangNouvAdherant = rechercherUnAdherant(*tAdherant, *nbElemAdhearant, adherantTmp.id, &trouve);

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
	unsigned int rangJeu;
	Bool trouve;
	Jeu* jeuSelect;
	CodeErreur cErr;

	printf("Fonction d'affichage de la liste des ");
	if (isReservation)
		printf("reservations ");
	else
		printf("emprunts ");
	printf ("concernant un jeu.");
	fflush(stdout);

	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return;

	if (trouve == FALSE)
		return;

	jeuSelect = tabJeu->jeux[rangJeu];
	if (trouve == FALSE)
		return;

	afficherListeERJeu(liste, jeuSelect->id);
}

void UTILE_InitNbJeuDispo(ListeEmprunt liste_Emprunt, TableauJeu* tabJeu)
{
	unsigned int rangJeu;
	Bool trouve;
	Jeu jeuIncompet;

	triTabJeu(tabJeu, ELEM_JEU_ID);

	for (unsigned int i = 0; i < tabJeu->nbElement; i++)
		tabJeu->jeux[i]->nbExemplaireDispo = tabJeu->jeux[i]->nbExemplaireTotal;


	while (liste_Emprunt != NULL)
	{
		jeuIncompet.id = liste_Emprunt->empRes.idJeu;
		rangJeu = rechercherJeu(tabJeu, &jeuIncompet, ELEM_JEU_ID, &trouve, TRUE);
		if (trouve == FALSE)
		{
			fprintf(stderr, "Erreur : un id d'empunts ne correspond pas aux id des jeux\n");
			exit(1);
		}
		tabJeu->jeux[rangJeu]->nbExemplaireDispo--;
		liste_Emprunt = liste_Emprunt->suiv;
	}
}
