#include "Adherant.h"

Adherant lireAdherant(FILE* flux)
{
	//Déclaration de variables utiles
	Adherant adherantEnCourDeLecture;
	char civilite;

	//Lecture de l'identifient et de la civilitée de l'adhérant
	fscanf(flux, "%d%*c", &(adherantEnCourDeLecture.id));
	civilite = fgetc(flux);

	//determination de la civilitée a partir d'information lu
	switch(civilite)
	{
		case 'H':
			adherantEnCourDeLecture.civilite = HOMME;
			break;
		case 'F':
			adherantEnCourDeLecture.civilite = FEMME;
			break;
		default:
			adherantEnCourDeLecture.civilite = INCONU;
			break;
	}

	//lecture du nom et du prénom de l'adhérant
	fscanf(flux, "%s%s%*c", adherantEnCourDeLecture.nom, adherantEnCourDeLecture.prenom);

	//Lecture de la date d'inscription de l'adhérant
	adherantEnCourDeLecture.dateInscri = lireDate(flux);

	return adherantEnCourDeLecture;
}

void afficheAdherant(Adherant ad, FILE* flux, Bool entete)
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

void afficheTabAdherant(Adherant tAdherant[], unsigned int nbElem, FILE* flux, Bool entete)
{
	if(entete)
		printf("ID  CIVILITÉE\tNOM\tPRENOM\tDate\n");
	for(unsigned int i=0; i<nbElem; ++i)
		afficheAdherant(tAdherant[i], flux, FALSE);
}

Adherant nouvAdherant(unsigned int id)
{
	Adherant tmp;
	char* espace = NULL;
	char civilite;
	tmp.id = id;

	//Traitement du prénom
	printf("Saisir le prenom\n>>>");
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
		scanf("%c%*c", &civilite);
	}
	while(civilite != 'F' && civilite != 'H');
	if(civilite == 'F')
		tmp.civilite = FEMME;
	else
		tmp.civilite = HOMME;


	//Traitement de la date d'inscription
	printf("Saisir la date du jour:\n");
	printf("Jour\t: "); scanf("%d%*c", &(tmp.dateInscri.jour));
	printf("Mois\t: "); scanf("%d%*c", &(tmp.dateInscri.mois));
	printf("Année\t: ");scanf("%d%*c", &(tmp.dateInscri.annee));

	return tmp;
}

int insererAdherant(Adherant* tAdherant[], unsigned int nbElem, unsigned int *tMax, Adherant* ad)
{
	Bool trouve;
	//Si le tableau est trop petit, l'agrandir de 10 espaces memoires
	if(nbElem >= *tMax)
	{
		*tMax = *tMax+10;
		Adherant *tmp = *tAdherant;
		*tAdherant = (Adherant*) malloc(sizeof(Adherant)*(*tMax));
		copieTabAdherant(tmp, nbElem, *tAdherant, *tMax);
		free(tmp);
		if(*tAdherant == NULL)
			return ERR_ALLOCATION;
	}

	unsigned int index = rechercherUnAdherant(*tAdherant, nbElem, ad->id, &trouve);
	if(trouve == TRUE)
	{
		fprintf(stderr, "L'adherant %d existe deja.\n", ad->id);
		return nbElem;
	}

	//Inserssion de l'Adherant
	decalageADroiteAdherant(*tAdherant, index, nbElem);
	(*tAdherant)[index] = *ad;

	return nbElem+1;
}

int supprimerAdherant(Adherant tAdherant[], unsigned int nbElem, Adherant* ad)
{
	Bool trouve;
	unsigned int index = rechercherUnAdherant(tAdherant, nbElem, ad->id, &trouve);
	if(trouve == FALSE)
	{
		fprintf(stderr, "L'adherant %d n'existe pas.\n", ad->id);
		return nbElem;
	}

	//suppression de l'Adherant de possistion index
	decalageAGaucheAdherant(tAdherant, index, nbElem);
	return nbElem-1;
}

void decalageAGaucheAdherant(Adherant tAdherant[], unsigned int debut, unsigned int nbElem)
{
	for(unsigned int i=debut; i>nbElem; ++i)
		tAdherant[i] = tAdherant[i+1];
}

void decalageADroiteAdherant(Adherant tAdherant[], unsigned int debut, unsigned int nbElem)
{
	for(unsigned int i=nbElem; i>debut; --i)
		tAdherant[i] = tAdherant[i-1];
}

unsigned int rechercherUnAdherant(Adherant tAdherant[], unsigned int nbElem, unsigned int id, Bool* trouve)
{
	int inf=0, sup=nbElem-1;
	int mil;

	*trouve = FALSE;
	while(inf <= sup)
	{
		mil = (inf+sup) / 2;
		if(id <= tAdherant[mil].id)
			sup = mil-1;
		else
			inf = mil+1;
	}
	if(tAdherant[inf].id == id)
		*trouve = TRUE;
	return inf;
}

int chargerLesAdherants(Adherant* tAdherant[], unsigned int* tMax, char nomDuFichier[])
{
	unsigned int nbElem = 0;
	Adherant tmp;
	FILE* flux = fopen(nomDuFichier, "r");
	if(flux == NULL)
		return ERR_OUVERTURE_FICHIER;

	//Temps que le currseur n'est pas a la fin du fichier,
	//convertire la ligne en cours de lecture en Adherant
	tmp = lireAdherant(flux);
	while(!feof(flux))
	{
		if(insererAdherant(tAdherant, nbElem, tMax, &tmp) == ERR_ALLOCATION)
			printf("Pb d'allocation dynamique lors du chargement\n");
		++nbElem;

		tmp = lireAdherant(flux);
	}
	fclose(flux);
	return nbElem;
}

Bool checkInscriptionValide(Adherant* ad, Date* dateDuJour) {return dateCmp(*dateDuJour, ad->dateInscri) < 365;}

void renouvelerInscription(Adherant* ad, Date* nouvelleDate)
{
	//Juste une réaffectation si l'inscription n'est pas valide
	if(checkInscriptionValide(ad, nouvelleDate))
		return;
	ad->dateInscri.jour = nouvelleDate->jour;
	ad->dateInscri.mois = nouvelleDate->mois;
	ad->dateInscri.annee = nouvelleDate->annee;

}

CodeErreur sauvegarderAdherant(Adherant tAdherant[], unsigned int nbElem, char nomDuFichier[])
{
	FILE* flux = fopen(nomDuFichier, "w");
	if(flux == NULL)
		return ERR_OUVERTURE_FICHIER;

	//Écrire le Tableau comportant tout les Adherants (trié) dans le fichier nomDuFichier
	afficheTabAdherant(tAdherant, nbElem, flux, FALSE);

	fclose(flux);

	return ERR_NO_ERR;
}

CodeErreur copieTabAdherant(Adherant tAdherant1[], unsigned int nbElem1, Adherant tAdherant2[], unsigned int tMax2)
{
	//Si le tableau à copier comporte plus d'element que la taille maximum du tableauqui reçoit les données,
	//Alors, on retourne une erreur de type OUT OF RANGE
	if(nbElem1 > tMax2)
		return ERR_OUT_OF_RANGE;

	for(unsigned int i=0; i<nbElem1; ++i)
		tAdherant2[i] = tAdherant1[i];
	return ERR_NO_ERR;
}
