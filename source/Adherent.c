#include "Adherent.h"

Adherent lireAdherent(FILE* flux)
{
	//Déclaration de variables utiles
	Adherent adherentEnCourDeLecture;
	char civilite;

	//Lecture de l'identifient et de la civilitée de l'adhérant
	fscanf(flux, "%d%*c", &(adherentEnCourDeLecture.id));
	civilite = fgetc(flux);

	//determination de la civilitée a partir d'information lu
	switch(civilite)
	{
		case 'H':
			adherentEnCourDeLecture.civilite = HOMME;
			break;
		case 'F':
			adherentEnCourDeLecture.civilite = FEMME;
			break;
		default:
			adherentEnCourDeLecture.civilite = INCONU;
			break;
	}

	//lecture du nom et du prénom de l'adhérant
	fscanf(flux, "%s%s%*c", adherentEnCourDeLecture.nom, adherentEnCourDeLecture.prenom);

	//Lecture de la date d'inscription de l'adhérant
	adherentEnCourDeLecture.dateInscri = lireDate(flux);

	return adherentEnCourDeLecture;
}

void afficheAdherent(Adherent ad, FILE* flux, Bool entete)
{
	//affichage d'une entete si le flux est la sortie standard
	if(flux == stdout && entete)
		printf("ID  CIVILITÉE\tNOM\tPRENOM\tDate\n");

	//affichage de l'identifient et de la civilitée
	switch(ad.civilite)
	{
		case HOMME:
			fprintf(flux, "%d\tH\t", ad.id);
			break;
		case FEMME:
			fprintf(flux, "%d\tF\t", ad.id);
			break;
		default:
			fprintf(flux, "%d\tI\t", ad.id);
			break;
	}

	//affichage du reste des attributs de l'adhérant (nopm, prénom, date d'inscription)
	fprintf(flux, "%s\t%s\t", ad.nom, ad.prenom);
	afficherDate(ad.dateInscri, flux);
	fprintf(flux, "\n");
}

void afficheTabAdherent(Adherent tAdherent[], unsigned int nbElem, FILE* flux, Bool entete)
{
	if(entete)
		printf("ID  CIVILITÉE\tNOM\tPRENOM\tDATEINSCRIPTION\n");
	for(unsigned int i=0; i<nbElem; ++i)
		afficheAdherent(tAdherent[i], flux, FALSE);
}

Adherent nouvAdherent(unsigned int id, Date dateDuJour)
{
	Adherent tmp;
	char* espace = NULL;
	char civilite;
	tmp.id = id;

	//Traitement du prénom
	printf("Saisir le prenom\n>>>");
	fflush(stdout);
	fgets(tmp.prenom, 21, stdin);

	tmp.prenom[strlen(tmp.prenom)-1] = '\0';
	espace = strchr(tmp.prenom, ' ');

	while(espace != NULL)//tant qu'il y a des espaces dans le prénom, les remplacer par des '-'
	{
		*espace = '-';
	 	espace = strchr(tmp.prenom, ' ');
	}


	//Traitement du nom
	printf("Saisir le nom\n>>>");
	fflush(stdout);
	fgets(tmp.nom, 21, stdin);

	tmp.nom[strlen(tmp.nom)-1] = '\0';
	espace = strchr(tmp.nom, ' ');

	while(espace != NULL)//tant qu'il y a des espaces dans le nom, les remplacer par des '-'
	{
	 	*espace = '-';
	 	espace = strchr(tmp.nom, ' ');
	}


	//Traitement de la Civilitée
	do
	{
		printf("Civilitée(H/F)\t: ");
		fflush(stdout);
		scanf("%c%*c", &civilite);
	}
	while(civilite != 'F' && civilite != 'H');
	if(civilite == 'F')
		tmp.civilite = FEMME;
	else
		tmp.civilite = HOMME;


	//Traitement de la date d'inscription
	tmp.dateInscri = dateDuJour;


	return tmp;
}

int insererAdherent(Adherent* tAdherent[], unsigned int nbElem, unsigned int *tMax, Adherent* ad)
{
	Bool trouve;
	//Si le tableau est trop petit, l'agrandir de 10 espaces memoires
	if(nbElem >= *tMax)
	{
		*tMax = *tMax+10;
		Adherent *tmp = *tAdherent;											//variable temporaire contenant l'addresse du tableau d'Adherent
		*tAdherent = (Adherent*) malloc(sizeof(Adherent)*(*tMax));			//allocation d'un tableau superieur de 10 cases memoires par rapport au précédant
		if(copieTabAdherent(tmp, nbElem, *tAdherent, *tMax) != ERR_NO_ERR)	//copie les valeur du premier tableau dans le deuxieme et arret de la fonction
			return ERR_OPERATION_INVALIDE;									//en cas de problèmes
		free(tmp);															//liberation du tableau precedant
		if(*tAdherent == NULL)												//gestion des erreurs d'allocations
			return ERR_ALLOCATION;
	}

	//Verifie si l'Adherent n'existe pas déjà, au quelle cas, on stop la fonction
	unsigned int index = rechercherUnAdherent(*tAdherent, nbElem, ad->id, &trouve);
	if(trouve == TRUE)
	{
		fprintf(stderr, "L'adherent %d existe deja.\n", ad->id);
		return nbElem;
	}

	//Inserssion de l'Adherent
	decalageADroiteAdherent(*tAdherent, index, nbElem);
	(*tAdherent)[index] = *ad;

	return nbElem+1;
}

int supprimerAdherent(Adherent tAdherent[], unsigned int nbElem, unsigned int id)
{
	Bool trouve;

	//Verifie si l'Adherent n'existe pas, au quelle cas, on stop la fonction
	unsigned int index = rechercherUnAdherent(tAdherent, nbElem, id, &trouve);
	if(trouve == FALSE)
	{
		fprintf(stderr, "L'adherent %d n'existe pas.\n", id);
		return nbElem;
	}

	//suppression de l'Adherent de possistion index
	decalageAGaucheAdherent(tAdherent, index, nbElem);
	return nbElem-1;
}

void decalageAGaucheAdherent(Adherent tAdherent[], unsigned int debut, unsigned int nbElem)
{
	for(unsigned int i=debut; i>nbElem; ++i)
		tAdherent[i] = tAdherent[i+1];
}

void decalageADroiteAdherent(Adherent tAdherent[], unsigned int debut, unsigned int nbElem)
{
	for(unsigned int i=nbElem; i>debut; --i)
		tAdherent[i] = tAdherent[i-1];
}

unsigned int rechercherUnAdherent(Adherent tAdherent[], unsigned int nbElem, unsigned int id, Bool* trouve)
{
	int inf=0, sup=nbElem-1;
	int mil;

	*trouve = FALSE;

	//Algorythme addapté pour les Adherents
	while(inf <= sup)
	{
		mil = (inf+sup) / 2;
		if(id <= tAdherent[mil].id)
			sup = mil-1;
		else
			inf = mil+1;
	}
	if(tAdherent[inf].id == id)
		*trouve = TRUE;
	return inf;
}

int chargerLesAdherents(Adherent* tAdherent[], unsigned int* tMax, char nomDuFichier[])
{
	unsigned int nbElem = 0;
	Adherent tmp;
	FILE* flux = fopen(nomDuFichier, "r");
	if(flux == NULL)
		return ERR_OUVERTURE_FICHIER;

	//Temps que le currseur n'est pas a la fin du fichier,
	//convertire la ligne en cours de lecture en Adherent
	tmp = lireAdherent(flux);
	while(!feof(flux))
	{
		if(insererAdherent(tAdherent, nbElem, tMax, &tmp) == ERR_ALLOCATION)
			printf("Pb d'allocation dynamique lors du chargement\n");
		++nbElem;

		tmp = lireAdherent(flux);
	}
	fclose(flux);
	return nbElem;
}

Bool checkInscriptionValide(Adherent* ad, Date* dateDuJour)
{
	return dateCmp(*dateDuJour, ad->dateInscri) < 365;
}

CodeErreur renouvelerInscription(Adherent* ad, Date* nouvelleDate)
{
	//Juste une réaffectation si l'inscription n'est pas valide
	if(checkInscriptionValide(ad, nouvelleDate))
		return ERR_OPERATION_INVALIDE;
	ad->dateInscri = *nouvelleDate;
	return ERR_NO_ERR;

}

CodeErreur sauvegarderAdherent(Adherent tAdherent[], unsigned int nbElem, char nomDuFichier[])
{
	FILE* flux = fopen(nomDuFichier, "w");
	if(flux == NULL)
		return ERR_OUVERTURE_FICHIER;

	//Écrire le Tableau comportant tout les Adherents (trié) dans le fichier nomDuFichier
	afficheTabAdherent(tAdherent, nbElem, flux, FALSE);

	fclose(flux);

	return ERR_NO_ERR;
}

CodeErreur copieTabAdherent(Adherent tAdherent1[], unsigned int nbElem1, Adherent tAdherent2[], unsigned int tMax2)
{
	//Si le tableau à copier comporte plus d'element que la taille maximum du tableauqui reçoit les données,
	//Alors, on retourne une erreur de type OUT OF RANGE
	if(nbElem1 > tMax2)
		return ERR_OUT_OF_RANGE;

	for(unsigned int i=0; i<nbElem1; ++i)
		tAdherent2[i] = tAdherent1[i];
	return ERR_NO_ERR;
}

unsigned int rechercherIDAdherentLibre(Adherent tAdherent[], unsigned int nbElem)
{
	unsigned int i;
	//Pour chaque Adherent du tableau trié, si son id est differant de sa possistion dans
	//le tableau, ça veut dire qu'il y à un trou et que l'id est donc libre pour la valeur atteinte
	//si il n'y a pas de "trou", la boncle arive à la fin du tableau et retourne donc le deriner id+1
	for(i=0; i<nbElem; ++i)
		if(tAdherent[i].id-i != 0)
			return i;
	return i;
}
