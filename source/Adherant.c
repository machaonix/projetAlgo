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
	printf("%s\t%s\t", ad.nom, ad.prenom);
	afficherDate(ad.dateInscri, flux);
	printf("\n");
}

void afficheTabAdherant(Adherant tAdherant[], unsigned int nbElem, FILE* flux, Bool entete)
{
	if(entete)
		printf("ID  CIVILITÉE\tNOM\tPRENOM\tDate\n");
	for(unsigned int i=0; i<nbElem; ++i)
		afficheAdherant(tAdherant[i], flux, FALSE);
}

int insererAdherant(Adherant tAdherant[], unsigned int nbElem, unsigned int *tMax, Adherant* ad)
{
	if(nbElem == *tMax)
	{
		*tMax = *tMax+10;
		tAdherant = realloc(tAdherant, sizeof(Adherant)*(*tMax));
		if(tAdherant == NULL)
			return ERR_ALLOCATION;
	}

	CodeErreur trouve;
	int index = rechercherUnAdherant(tAdherant, nbElem, ad, &trouve);
	
	if(index == ERR_EXISTE_DEJA)
	{
		fprintf(stderr, "L'adherant %d existe deja.\n", ad->id);
		return nbElem;
	}

	decalageADroiteAdherant(tAdherant, index, nbElem);
	tAdherant[index] = *ad;
	// printf("->\n");
	// for(int i=0; i<index; ++i)
	// 	printf("%d\n", tAdherant[index].id);

	return nbElem+1;
}

int supprimerAdherant(Adherant tAdherant[], unsigned int nbElem, Adherant* ad)
{
	CodeErreur trouve;
	int index = rechercherUnAdherant(tAdherant, nbElem, ad, &trouve);
	if(trouve == ERR_NOT_FOUND)
	{
		fprintf(stderr, "L'adherant %d n'existe pas.\n", ad->id);
		return nbElem;
	}

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

int rechercherUnAdherant(Adherant tAdherant[], unsigned int nbElem, Adherant* ad, CodeErreur* trouve)
{
	int inf=0, sup=nbElem-1;
	int mil;

	*trouve = ERR_NOT_FOUND;
	while(inf <= sup)
	{
		mil = (inf+sup) / 2;
		if(ad->id <= tAdherant[mil].id)
			sup = mil-1;
		else
			inf = mil+1;
	}
	if(tAdherant[inf].id == ad->id)
		*trouve = ERR_EXISTE_DEJA;
	return inf;
}

int chargerLesAdherants(Adherant tAdherant[], unsigned int *tMax, char nomDuFichier[])
{
	unsigned int nbElem = 0;
	Adherant tmp;
	FILE* flux = fopen(nomDuFichier, "r");
	if(flux == NULL)
		return ERR_OUVERTURE_FICHIER;

	tmp = lireAdherant(flux);
	while(!feof(flux))
	{
		insererAdherant(tAdherant, nbElem, tMax, &tmp);
		++nbElem;

		tmp = lireAdherant(flux);

	}
	fclose(flux);
	return nbElem;
}