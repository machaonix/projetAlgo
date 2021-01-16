#include "Ludotheque.h"

/*
		afficheMenu
Description :
	Affiche les differentes actions possibles, ainsi que leurs numéros
*/
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
	printf("%d)\tNouvel adherent\n", CHOIX_NOUV_ADHERANT);
	printf("%d)\tRenouveler un abonement\n", CHOIX_RENOUV_ADHERANT);
	printf("%d)\tAfficher liste des adherents\n", CHOIX_AFFICHE_ADHERANT);
	printf("%d)\tAfficher liste des emprunts en cours\n", CHOIX_AFFICHE_EMPRUNT);
	printf("%d)\tAfficher liste des reservations en cours\n", CHOIX_AFFICHE_RESERVATION);
	printf("%d)\tAfficher la liste des reservations pour un jeu\n", CHOIX_AFFICHE_RESERVATION_JEU);
	printf("%d)\tAfficher la liste des emprunt pour un jeu\n", CHOIX_AFFICHE_EMPRUNT_JEU);
	printf("%d)\tSauvegarder\n", CHOIX_SAUVEGARDER);
	printf("%d)\tQuitter\n", CHOIX_QUITTER);
}

/*
		Ludotheque
Description :
	Fonction globale de l'application : déclare, charge et initalise les tableaux et listes necessaires au bon fonctionnement de l'application.
*/
void Ludotheque(void)
{
	TableauJeu tabJeu;
	Adherent *tAdherent;
	unsigned int tMaxAdherent = 2;
	int nbElemAdherent;
	ListeER liste_Emprunt=listeER_Vide(), liste_Reservation=listeER_Vide();
	unsigned int nb_Emprunt, nb_Reservation;
	unsigned int reponceDuMenu;
	Bool lance = TRUE;
	CodeErreur cErr;
	Date dateDuJour;


	//initialisation et chargement
	initTabJeu(&tabJeu);
 	cErr = chargerTabJeu(&tabJeu, "donnee/jeux.don");
 	if (cErr != ERR_NO_ERR) return;

	tAdherent = (Adherent*) malloc(sizeof(Adherent)*tMaxAdherent);
	nbElemAdherent = chargerLesAdherents(&tAdherent, &tMaxAdherent, "donnee/adherent.don");
	if(nbElemAdherent < 0) return;

	liste_Emprunt=chargerListeEmpruntReservation("donnee/emprunts.don",&nb_Emprunt);
  	liste_Reservation=chargerListeEmpruntReservation("donnee/reservations.don",&nb_Reservation);

	UTILE_InitNbJeuDispo(liste_Emprunt,&tabJeu);


	printf("Saisir la date du jour (JJ/MM/YYYY):");
	fflush(stdout);
	dateDuJour = lireDate(stdin);

	//Menu
	while(lance)
	{
		//Affichage
		afficheMenu();
		printf("\n>>>");
		fflush(stdout);

		//Choix utilisateur
		scanf("%u%*c", &reponceDuMenu);

		//Réaction au choix
		switch(reponceDuMenu)
		{
			case CHOIX_ANNULER_RESERVATION:
				 if(GLOBAL_Anuller_Reservation(&liste_Reservation, &nb_Reservation, tAdherent, nbElemAdherent, &tabJeu))
				 	printf("Réservation annulé avec succès\n");
				break;
			case CHOIX_EMPRUNTER:
				GLOBAL_Emprunter(&liste_Reservation, &nb_Reservation, &liste_Emprunt, &nb_Emprunt, &tabJeu, &tAdherent, &nbElemAdherent, &tMaxAdherent, dateDuJour);
				break;
			case CHOIX_RETOUR_JEU:
				GLOBAL_RetourJeu(tAdherent, nbElemAdherent, &tabJeu, &liste_Emprunt, &nb_Emprunt, &liste_Reservation, dateDuJour);
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
				GLOBAL_NouvelAdherent(&tAdherent, &nbElemAdherent, &tMaxAdherent, NULL, dateDuJour);
				break;
			case CHOIX_RENOUV_ADHERANT:
				GLOBAL_RenouvellerAdherent(tAdherent, nbElemAdherent, dateDuJour);
				break;
			case CHOIX_AFFICHE_ADHERANT:
				afficheTabAdherent(tAdherent, nbElemAdherent, stdout, TRUE);
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
				if (!GLOBAL_Sauvegarder(&tabJeu, tAdherent, nbElemAdherent, liste_Reservation, nb_Reservation, liste_Emprunt, nb_Emprunt))
					printf("Une erreur à perturbé la sauvegarde\n");
				break;
			case CHOIX_QUITTER:
				if (IO_Choix_O_N("Souhaitez vous sauvegarder avant de quitter"))
					if (!GLOBAL_Sauvegarder(&tabJeu, tAdherent, nbElemAdherent, liste_Reservation, nb_Reservation, liste_Emprunt, nb_Emprunt))
						if (!IO_Choix_O_N("Un erreur à perturbé la sauvegarde, souhaitez vous tout de meme quitter"))
							break;
				lance = FALSE;
				break;
			default:
				printf("Instruction Invalide\n");
				break;

		}
	}


	//Libération de la mémoire
	supprimerListe(liste_Reservation);
	supprimerListe(liste_Emprunt);
	libererTabJeu(&tabJeu);
	free(tAdherent);

}


/*
		GLOBAL_RetourJeu
Description :
	Permet de retourner un jeu

Valeur de retour :
	Si retour effectué -> TRUE
	Sinon -> FALSE

Arguments :
	Adherent tAdherent[] -> Le tableau d'adhérants
	unsigned int nbElemAdherent -> Nombre d'adhérants
	TableauJeu* tabJeu -> Le tableau de jeux
	ListeEmprunt* liste_Emprunt -> Liste d'emprunts
	unsigned int* nb_Emprunt -> Nombre d'emprunts
	ListeReservation* liste_Reservation -> La liste des reservations (pour savoir si le jeu doit-être transmis)
	Date dateDuJour -> La date du jour
*/
Bool GLOBAL_RetourJeu(Adherent tAdherent[], unsigned int nbElemAdherent, TableauJeu* tabJeu, ListeEmprunt* liste_Emprunt, unsigned int* nb_Emprunt, ListeReservation* liste_Reservation, Date dateDuJour)
{
	unsigned int idAdherent, idEmprunt;
	unsigned int rangJeu, rangAdherent;
	Jeu* jeuEmprunte;
	Emprunt emprunt;
	Bool trouve;
	CodeErreur cErr;

	//Recherche de l'adérant concerné
	printf("Entrez l'ID de l'adherent\n>>>");
	fflush(stdout);
	scanf("%u%*c", &idAdherent);
	rechercherUnAdherent(tAdherent, nbElemAdherent, idAdherent, &trouve);
	if(!trouve)
	{
		fprintf(stderr, "Cet adherent n'existe pas\n");
		return FALSE;
	}

	//Recherche du Jeu retourné
	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return FALSE;

	if (trouve == FALSE)
		return FALSE;

	jeuEmprunte = tabJeu->jeux[rangJeu];

	//Recherche de l'emprunt en question
	idEmprunt = rechercherListeER_AdJeu(*liste_Emprunt, idAdherent, jeuEmprunte->id, &trouve);
	if (trouve == FALSE)
	{
		fprintf(stderr, "Cet adherent n'a pas emprunté ce jeu\n");
		return FALSE;
	}

	//Recherche d'une reservation pour ce jeu
	rechercherListeER_Jeu(*liste_Reservation, jeuEmprunte->id, &trouve);
	if (trouve)
	{
		//Recherche de la plus vielle reservation pour ce jeu pour le transmettre à l'adherent ayant reservé le premier
		emprunt = plusVieilleReservationJeu(*liste_Reservation, jeuEmprunte->id);

		rangAdherent = rechercherUnAdherent(tAdherent, nbElemAdherent, emprunt.idAdherent, &trouve);
		if (trouve == FALSE)
		{
			fprintf(stderr, "Cet adherent n'existe pas\n");
			return FALSE;
		}

		//Suppression de la reservation
		*liste_Reservation = supprimerEmpruntReservation(*liste_Reservation, emprunt.id, nb_Emprunt, &cErr);

		//Création d'un nouvel identifiant et mise à jour de la date
		emprunt.id = rechercherIdLibre(*liste_Emprunt);
		emprunt.date = dateDuJour;

		//Ajout de ce nouvel emprunt à la liste d'emprunts
		*liste_Emprunt=insererEmpruntReservation(*liste_Emprunt, nb_Emprunt, emprunt);
		//Message indiquant le transfert
		printf("%s %s a reserver le jeu, la reservation devient un emprunt\n",tAdherent[rangAdherent].prenom, tAdherent[rangAdherent].nom);
	}


	//Suppression de l'emprunt
	*liste_Emprunt = supprimerEmpruntReservation(*liste_Emprunt, idEmprunt, nb_Emprunt, &cErr);
	if (cErr != ERR_NO_ERR)
	{
		fprintf(stderr, "Erreur de suppression\n");
		return FALSE;
	}

	return TRUE;
}

/*
		GLOBAL_ModifierSupprimerJeu
Description :
	Permet de modifier ou de supprimer un jeu sans risquer de corrompre des emprunts ou des reservations

Valeur de retour :
	Si l'opération voulu à été effectué -> TRUE
	Sinon -> FALSE

Arguments :
	TableauJeu* tabJeu -> Le tableau de jeux
	ListeReservation* liste_Reservation -> La liste des reservations
	unsigned int* nb_Reservation -> Nombre de reserations
	ListeEmprunt liste_Emprunt -> Liste d'emprunts
*/
Bool GLOBAL_ModifierSupprimerJeu(TableauJeu* tabJeu, ListeReservation* liste_Reservation, unsigned int* nb_Reservation, ListeEmprunt liste_Emprunt)
{
	Bool trouve;
	Bool supprimable = TRUE;
	unsigned int rangJeu;
	Jeu* jeu;
	unsigned int idER;
	ElementJeu elementJeuAModifier;
	unsigned int nbMinExemplaireTotal;
	CodeErreur cErr;

	//Recherche du jeu à modifier ou supprimer
	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return FALSE;

	if (trouve == FALSE)
		return FALSE;

	jeu = tabJeu->jeux[rangJeu];

	//Si le jeu est emprunté, il est interdit de le supprimer
	idER = rechercherListeER_Jeu(liste_Emprunt, jeu->id, &trouve);
	if (trouve)
	{
		printf("Ce jeu est actuellement emprunter: notemment identifiant %u\n", idER);
		supprimable = FALSE;
	}

	//Si le jeu est reservé, il est interdit de le supprimer, à moins d'annuler toutes les reservations le concernant
	idER = rechercherListeER_Jeu(*liste_Reservation, jeu->id, &trouve);
	if (trouve)
	{
		printf("Ce jeu est actuellement reserver: notemment identifiant %u\n", idER);
		if (IO_Choix_O_N("Souhaiter vous annuler toutes ces reservations"))
		{
			//Annulation de toutes les reservations pour le jeu
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
			supprimable = FALSE;
		}
	}

	printf("\n");
	afficheJeu(jeu, stdout);
	//Si le jeu est supprimable, on demande si il s'agit de l'action que l'utilisateur veut effectuer
	if (supprimable)
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

	//On demande si l'utilisateur veut modifier le jeu
	if (IO_Choix_O_N("\nSouhaitez vous modifier le jeu"))
	{
		//Choix de l'élément de modification
		elementJeuAModifier = choisirElementJeu("modifier le jeu ci dessus");
		//3 sécurités pour empécher ou restreindre certaines actions
		if (elementJeuAModifier == ELEM_JEU_ID)
		{
			printf("Il n'est pas autorisé de modifier l'identifiant d'un jeu'\n");
			return FALSE;
		}
		if (elementJeuAModifier == ELEM_JEU_NB_EXEMPLAIRE_DISPO)
		{
			printf("Il n'est pas autorisé de modifier le nombre d'exemplaires disponibles\n");
			return FALSE;
		}
		if (elementJeuAModifier == ELEM_JEU_NB_EXEMPLAIRE_TOTAL)
		{
			nbMinExemplaireTotal = jeu->nbExemplaireTotal - jeu->nbExemplaireDispo;
		}

		//Entrée de la nouvelle valeur
		cErr = entrerValeurElementJeu(jeu, elementJeuAModifier);
		if (cErr != ERR_NO_ERR)
		{
			printf("Erreur lors de la modification\n");
			return FALSE;
		}
		//Test de limite
		if (jeu->nbExemplaireTotal<nbMinExemplaireTotal)
		{
			printf("Il n'est pas autorisé d'assigner une valeur inferieur au nombres d'exemplaires empruntés.\n");
			printf("Le nombre total d'exemplaire est assigné à la valeur minimal possible\n");
			jeu->nbExemplaireTotal = nbMinExemplaireTotal;
		}

		//Modification du nombre d'exemplaires disponible en fonction du nouveau nombre d'exemplaire total
		if (elementJeuAModifier == ELEM_JEU_NB_EXEMPLAIRE_TOTAL)
		{
			jeu->nbExemplaireDispo = jeu->nbExemplaireTotal - nbMinExemplaireTotal;
		}
		printf("Jeu modifié :");
		afficheJeu(jeu,stdout);
		printf("\n");
		return TRUE;
	}


	return FALSE;
}

/*
		GLOBAL_Anuller_Reservation
Description :
	Permet d'annuler une réservation.

Valeur de retour :
	Si retour effectué -> TRUE
	Sinon -> FALSE

Arguments :
	ListeReservation* liste_Reservation -> pointeur pour faire passer la liste des réservation
	unsigned int* nb_Reservation -> pointeur sur le nombre d'élément de la liste
	Adherent tAdherent[] -> tableau d'adhérent
	unsigned int nbElemAdherent -> nombre d'adhérant dans le tableau
	TableauJeu* tabjeu -> pointeur vers le tableau contenant les jeux
*/
Bool GLOBAL_Anuller_Reservation(ListeReservation* lr, unsigned int* nb_Reservation, Adherent tAdherent[], unsigned int nbElemAdherent, TableauJeu* tabJeu)
{
	unsigned int idAdherent, idReservation;
	unsigned int rangJeu;
	Jeu* jeuReserve;
	Bool trouve;
	CodeErreur cErr;

	printf("Entrez l'ID de l'adherent\n>>>");
	fflush(stdout);
	scanf("%u%*c", &idAdherent);
	rechercherUnAdherent(tAdherent, nbElemAdherent, idAdherent, &trouve);
	if(!trouve)
	{
		fprintf(stderr, "Cet adherent n'existe pas\n");
		return FALSE;
	}

	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return FALSE;

	if (trouve == FALSE)
		return FALSE;

	jeuReserve = tabJeu->jeux[rangJeu];

	idReservation = rechercherListeER_AdJeu(*lr, idAdherent, jeuReserve->id, &trouve);
	if(!trouve)
	{
		fprintf(stderr, "L'adherent %d n'as pas réservé le jeu %d\n", idAdherent, jeuReserve->id);
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

/*
		GLOBAL_Emprunter
Description :
	Permet de créer un emprunt ou une reservation si le jeu est indisponible

Valeur de retour :
	Si retour effectué -> TRUE
	Sinon -> FALSE

Arguments :
	ListeReservation* liste_Reservation -> pointeur pour faire passer la liste des réservation
	unsigned int* nb_Reservation -> pointeur sur le nombre d'élément de la liste
	ListeEmprunt* liste_Emprunt -> pointeur pour faire passer la liste des réservation
	unsigned int* nb_Emprunt -> pointeur sur le nombre d'élément de la liste
	TableauJeu* tabjeu -> pointeur vers le tableau contenant les jeux
	Adherent tAdherent[] -> tableau d'adhérent
	unsigned int nbElemAdherent -> nombre d'adhérant dans le tableau
	unsigned int* tMaxAdhrant -> nombre maximum d'élément dans le tableau
	Date dateDuJour -> date du jour (entrée au lancement du programme)
*/
Bool GLOBAL_Emprunter(ListeReservation* liste_Reservation, unsigned int* nb_Reservation, ListeEmprunt* liste_Emprunt, unsigned int* nb_Emprunt, TableauJeu* tabJeu, Adherent* tAdherent[], int* nbElemAdherent, unsigned int* tMaxAdherent, Date dateDuJour)
{
	EmpruntReservation er;

	ListeER** liste;
	unsigned int** nb_elem;

	Bool trouve;
	unsigned int rangAdherent;
	unsigned int rangJeu;
	Jeu* jeuAEmprunter;

	CodeErreur cErr;


	er.date = dateDuJour;


	if(IO_Choix_O_N("Est-ce un nouvel adherent"))
	{
		if(!GLOBAL_NouvelAdherent(tAdherent, nbElemAdherent, tMaxAdherent, &rangAdherent, dateDuJour))
		{
			printf("Reservation avortée\n");
			return FALSE;
		}
		er.idAdherent = (*tAdherent)[rangAdherent].id;
	}
	else
	{
		printf("Quel est l'identifiant de l'adherent: ");
		fflush(stdout);
	  	scanf("%u%*c",&(er.idAdherent));

	  	rangAdherent = rechercherUnAdherent(*tAdherent, *nbElemAdherent, er.idAdherent, &trouve);
	  	if (trouve == FALSE)
	  	{
	  		printf("Veuillez donner un id valable : ");
	  		fflush(stdout);
	  		scanf("%u%*c",&(er.idAdherent));

	  		rangAdherent = rechercherUnAdherent(*tAdherent, *nbElemAdherent, er.idAdherent, &trouve);
	  	}

	  	if (checkInscriptionValide(&((*tAdherent)[rangAdherent]), &er.date) == FALSE)
	  	{
	  		if(IO_Choix_O_N("Cet adherent n'a plus une insciption valide, voulez vous renouveller son abonement"))
	  		{
	  			if(!GLOBAL_RenouvellerAdherent(*tAdherent, *nbElemAdherent, dateDuJour))
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
	//id adherent valable


	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return FALSE;

	if (trouve == FALSE)
		return FALSE;

	jeuAEmprunter = tabJeu->jeux[rangJeu];


	//rechercher un emprunt avec l'id de l'adherent et et celui du jeu
	rechercherListeER_AdJeu(*liste_Emprunt,  er.idAdherent, jeuAEmprunter->id, &trouve);
	if (trouve)
	{
		printf("Cette adherent à déjà un emprunt en cours pour ce jeu\n");
	  	printf("Reservation avortée\n");
	  	return FALSE;
	}

	//rechercher une reseration avec l'id de l'adherent et et celui du jeu
	rechercherListeER_AdJeu(*liste_Reservation,  er.idAdherent, jeuAEmprunter->id, &trouve);
	if (trouve)
	{
		printf("Cette adherent à déjà reserver en cours pour ce jeu\n");
		printf("Reservation avortée\n");
		return FALSE;
	}

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


	er.idJeu =  jeuAEmprunter->id;
	er.id = rechercherIdLibre(**liste);

	**liste = insererEmpruntReservation(**liste, *nb_elem, er);

	return TRUE;
}

/*
		GLOBAL_NouvelAdherent
Description :
	Acompagne l'enregistrement d'un adhérent

Valeur de retour :
	Si enregistrement effectué -> TRUE
	Sinon -> FALSE

Arguments :
	Adherent* tAdherent[] -> tableau d'adhérent
	unsigned int* nbElemAdherent -> nombre d'adhérant dans le tableau
	unsigned int* tMaxAdhrant -> nombre maximum d'élément dans le tableau
	unsigned int* rangNouvAdherent -> (peut-être NULL) si non NULL, se voit assigner le rang de l'adhérant nouvellement enregistré
	Date dateDuJour -> date du jour (entrée au lancement du programme)
*/
Bool GLOBAL_NouvelAdherent(Adherent* tAdherent[], int* nbElemAdherent, unsigned int* tMaxAdherent, unsigned int* rangNouvAdherent, Date dateDuJour)
{
	Adherent adherentTmp;
	Bool trouve;

	adherentTmp = nouvAdherent(rechercherIDAdherentLibre(*tAdherent, *nbElemAdherent), dateDuJour);
	*nbElemAdherent = insererAdherent(tAdherent, *nbElemAdherent, tMaxAdherent, &adherentTmp);
	if(*nbElemAdherent >= 0)
	{
		if (rangNouvAdherent != NULL)
			*rangNouvAdherent = rechercherUnAdherent(*tAdherent, *nbElemAdherent, adherentTmp.id, &trouve);

		printf("Nouvel adherent enregistrer avec succès\n");
		return TRUE;
	}
	else
	{
		printf("Une erreur a eu lieux lors de l'enregistrement : %d\n", *nbElemAdherent);
		return FALSE;
	}
}

/*
		GLOBAL_RenouvellerAdherent
Description :
	Permet le renouvellement d'une inscription.

Valeur de retour :
	Si renouvellement effectué -> TRUE
	Sinon -> FALSE

Arguments :
	Adherent* tAdherent[] -> tableau d'adhérent
	unsigned int* nbElemAdherent -> nombre d'adhérant dans le tableau
	Date dateDuJour -> date du jour (entrée au lancement du programme)
*/
Bool GLOBAL_RenouvellerAdherent(Adherent tAdherent[], unsigned int nbElemAdherent, Date dateDuJour)
{
	unsigned int idAdherentTmp, indexAdherent;
	float montantRemis;
	Bool trouveAdherent;


	printf("Saisir l'ID d'un adherent\n>>>");
	fflush(stdout);
	scanf("%u%*c", &idAdherentTmp);
	indexAdherent = rechercherUnAdherent(tAdherent, nbElemAdherent, idAdherentTmp, &trouveAdherent);
	printf("Montant remis\n>>>");
	fflush(stdout);
	scanf("%f%*c", &montantRemis);
	if(montantRemis < PRIX_ADHERENT)
	{
		printf("Le montant remis n'est pas sufissant, il manque %.2f€ (prix : %.2f€)", PRIX_ADHERENT-montantRemis, PRIX_ADHERENT);
		return FALSE;
	}

	renouvelerInscription(&(tAdherent[indexAdherent]), &dateDuJour);

	return TRUE;
}

/*
		GLOBAL_Sauvegarder
Description :
	Sauvegarde les differentes données

Valeur de retour :
	Si la sauvegarde s'est bien passée -> TRUE
	Sinon -> FALSE

Arguments :
	TableauJeu* tabJeu -> Le tableau de jeux
	Adherent tAdherent[] -> Le tableau d'adhérants
	unsigned int nbElemAdherent -> Nombre d'adhérants
	ListeReservation liste_Reservation -> La liste des reservations
	unsigned int nb_Reservation -> Nombre de reservations
	ListeEmprunt liste_Emprunt -> Liste d'emprunts
	unsigned int nb_Emprunt -> Nombre d'emprunts
*/
Bool GLOBAL_Sauvegarder(TableauJeu* tabJeu, Adherent tAdherent[], unsigned int nbElemAdherent, ListeReservation liste_Reservation, int nb_Reservation, ListeEmprunt liste_Emprunt, int nb_Emprunt)
{
	CodeErreur cErr;
	Bool sauvegardeEffectuee = TRUE;
	printf("Sauvegarde\n");
	cErr = sauvegarderTabJeu(tabJeu, "donnee/jeux.don");
	if (cErr != ERR_NO_ERR)
		sauvegardeEffectuee = FALSE;
	cErr = sauvegarderAdherent(tAdherent, nbElemAdherent, "donnee/adherent.don");
	if (cErr != ERR_NO_ERR)
		sauvegardeEffectuee = FALSE;
	cErr = sauvegarderListeER(liste_Emprunt, "donnee/emprunts.don", nb_Emprunt);
	if (cErr != ERR_NO_ERR)
		sauvegardeEffectuee = FALSE;
	cErr = sauvegarderListeER(liste_Reservation, "donnee/reservations.don", nb_Reservation);
	if (cErr != ERR_NO_ERR)
		sauvegardeEffectuee = FALSE;

	return sauvegardeEffectuee;
}

/*
		GLOBAL_afficherListeERJeu_Interactif
Description :
	Permet d'afficher les élément de la liste en fonction d'un jeu que la fonction demande à l'utilisateur.

Arguments :
	ListeER liste -> liste dans laquelle on effectue la recherche
	TableauJeu* tabJeu -> pointeur vers le tableau contenant les jeux
	Bool isReservation -> booleen indiquant si on affiche les réservations ou les emprunts
*/
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

	printf("\n");
	afficherListeERJeu(liste, jeuSelect->id);
}


/*
		UTILE_InitNbJeuDispo
Description :
	Initialise les nombres d'exemplaires disponibles pour chaque jeux

Arguments :
	ListeEmprunt liste_Emprunt -> Liste d'emprunts
	TableauJeu* tabJeu -> Le tableau de jeux
*/
void UTILE_InitNbJeuDispo(ListeEmprunt liste_Emprunt, TableauJeu* tabJeu)
{
	unsigned int rangJeu;
	Bool trouve;
	Jeu jeuIncompet;

	//Le tri par id permet de rechercher plus vite à l'aide des idJeu
	triTabJeu(tabJeu, ELEM_JEU_ID);

	//On initialise tout les nombres d'exemplaires disponibles au nombre total d'exemplaires
	for (unsigned int i = 0; i < tabJeu->nbElement; i++)
		tabJeu->jeux[i]->nbExemplaireDispo = tabJeu->jeux[i]->nbExemplaireTotal;

	//On parcourt la liste d'emprunt pour décrémenter le nombre d'exemplaires disponible des jeux empruntés
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
