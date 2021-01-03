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
	printf("%d)\tAfficher liste des emprunts en cours\n", CHOIX_EMPRUNTER);
	printf("%d)\tAfficher liste des reservations en cours\n", CHOIX_AFFICHE_RESERVATION);
	printf("%d)\tAfficher la liste des reservations pour un jeu\n", CHOIX_AFFICHE_RESERVATION_JEU);
	printf("%d)\tSauvegarder\n", CHOIX_SAUVEGARDER);
	printf("%d)\tQuitter\n", CHOIX_QUITTER);
}

void Ludotheque(void)
{
	TableauJeu tabJeu;
	int tMaxAdherant = 5, indexAdherant, idAdherantTmp;
	Adherant *tAdherant;
	int nbElemAdhearant;
	ListeER liste_Emprunt=listeER_Vide(),liste_Reservation=listeER_Vide();
	int nb_Emprunt,nb_Reservation;
	char reponceDuMenu;
	float montantRemis;
	Date dateTmp;
	Bool lance = TRUE;
	CodeErreur cErr, trouveAdherant;
	Adherant adherantTmp;
	
	char choix;
	
	//initialisation et chargement
	initTabJeu(&tabJeu);
 	cErr = chargerTabJeu(&tabJeu, "donnee/jeux.don");
 	if (cErr != ERR_NO_ERR) return;

	tMaxAdherant = chargerLesAdherants(&tAdherant, &tMaxAdherant, "donnee/adherant.don");
	if(tMaxAdherant < 0) return;
	
	liste_Emprunt=chargerListeEmpruntReservation("donnee/emprunts.don",&nb_Emprunt);
  	liste_Reservation=chargerListeEmpruntReservation("donnee/reservations.don",&nb_Reservation);
	
	//Menu
	while(lance)
	{
		afficheMenu();
		printf("\n>>>"); 
		scanf("%d%*c", &reponceDuMenu);
		switch(reponceDuMenu)
		{
			case CHOIX_RESERVER://////////////////////////////////////////////////////////

				break;
			case CHOIX_ANNULER_RESERVATION://////////////////////////////////////////////////////////
				break;
			case CHOIX_EMPRUNTER://////////////////////////////////////////////////////////
				break;
			case CHOIX_RETOUR_JEU://////////////////////////////////////////////////////////
				break;
			case CHOIX_AFFICHE_JEU:
				afficheTabJeu(&tabJeu);
				break;
			case CHOIX_TRIER_JEU:
				triTabJeuInteractif(&tabJeu);
				break;
			case CHOIX_NOUV_ADHERANT:
				adherantTmp = nouvAdherant(tAdherant[nbElemAdhearant-1].id+1);
				nbElemAdhearant = insererAdherant(&tAdherant, nbElemAdhearant, &tMaxAdherant, &adherantTmp);
				if(nbElemAdhearant >= 0)
					printf("Nouvel adherant enregistrer avec succès\n");
				else
					printf("Une erreur a eu lieux lors de l'enregistrement : %d\n", nbElemAdhearant);
				break;
			case CHOIX_RENOUV_ADHERANT:
				printf("Saisir l'ID d'un adherant\n>>>"); scanf("%d%*c", &idAdherantTmp);
				indexAdherant = rechercherUnAdherant(tAdherant, nbElemAdhearant, idAdherantTmp, &trouveAdherant);
				printf("Montant remis\n>>>"); scanf("%f%*d%*c", &montantRemis);
				if(montantRemis < PRIX_ADHERANT)
				{
					printf("Le montant remis n'est pas sufissant, il manque %.2f€ (prix : %.2f€)", PRIX_ADHERANT-montantRemis, PRIX_ADHERANT);
					break;
				}
				printf("Saisir la date du jour:\n");
				printf("Jour\t: "); scanf("%d%*c", &(dateTmp.jour));
				printf("Mois\t: "); scanf("%d%*c", &(dateTmp.mois));
				printf("Année\t: ");scanf("%d%*c", &(dateTmp.annee));
				renouvelerInscription(&(tAdherant[indexAdherant]), dateTmp);
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
				printf("Souhaitez vous sauvegarder avant de quitter (O/N) ? : ");
				scanf("%c%*c", &choix);
				while (choix != 'O' && choix != 'N')
				{
					printf("Veuillez par O ou par N : ");
					scanf("%c%*c", &choix);
				}
				if (choix == 'O')
					GLOBAL_Sauvegarder(&tabJeu, tAdherant, nbElemAdhearant, liste_Reservation, nb_Reservation, liste_Emprunt, nb_Emprunt);
				lance = FALSE;
				break;
			default:
				printf("Instruction Invalide\n");
				break;
			
		}
	}
}


void GLOBAL_Sauvegarder(TableauJeu* tabJeu, Adherant tAdherant[], unsigned int nbElemAdhearant, ListeReservation liste_Reservation, int nb_Reservation, ListeEmprunt liste_Emprunt, int nb_Emprunt)
{
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

	
	afficherListeERJeu(liste, idjeu);
}
