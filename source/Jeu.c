#include "Jeu.h"



void afficheJeu(Jeu* jeu, FILE* flux)
{
	fprintf(flux, "%d\t%s\t%d\t%s", jeu->id, jeu->type, jeu->nbExemplaireTotal, jeu->nom);
}

Jeu nouvJeu(unsigned int id)
{
	Jeu jeu;
	char choix = 'N';
	jeu.id = id;

	printf("Nom du jeu : ");
	fflush(stdout);
	fgets(jeu.nom, 41, stdin);
	jeu.nom[strlen(jeu.nom)-1] = '\0';

	printf("\nType du jeu : ");
	fflush(stdout);
	scanf("%s", jeu.type);

	printf("\nNombre d'exemplaires : ");
	fflush(stdout);
	scanf("%d%*c", &(jeu.nbExemplaireTotal));

	printf("\nSouhaitez vous integrer le jeu suivant (O/N) ?\n");
	afficheJeu(&jeu, stdout);
	printf("\n");
	fflush(stdout);
	scanf("%c%*c", &choix);
	if (choix == 'O')
		return jeu;

	return jeu;
}

void afficheTabJeu(Jeu* tJeu[], int nbElem, FILE* flux)
{
	if (flux == stdout)
		printf("\nId\tType\tNombre\tNom\n");
	for (int i = 0; i<nbElem; ++i)
	{
		afficheJeu(tJeu[i], flux);
		printf("\n");
	}
}

Jeu lireJeu(FILE* flux)
{
	Jeu jeu;
	fscanf(flux, "%d%s%d%*c", &(jeu.id), jeu.type, &(jeu.nbExemplaireTotal));
	fgets(jeu.nom, 41,flux);
	jeu.nom[strlen(jeu.nom)-1] = '\0';
	return jeu;
}

int chargerTabJeu(Jeu* tJeu[], char nomFichier[], int nbElemMax)
{
	FILE* flux;
	Jeu jeu;
	int i=0;

	flux = fopen(nomFichier, "r");
	if (!flux)
	{
		fprintf(stderr, "Erreur: ouverture fichier\n");
		return ERR_OUVERTURE_FICHIER;
	}

	jeu = lireJeu(flux);
	while(!feof(flux))
	{

		if (i==nbElemMax)
		{
			fprintf(stderr, "Erreur: taille de tableau de jeu trop petite\n");
			return ERR_OUT_OF_RANGE;
		}

		tJeu[i] = (Jeu*) malloc(sizeof(Jeu));
		if (tJeu[i] == NULL)
		{
			fprintf(stderr, "Erreur: probleme d'allocation\n");
			return ERR_ALLOCATION;
		}
		*tJeu[i] = jeu;

		jeu = lireJeu(flux);
		++i;
	}

	fclose(flux);

	return i;
}

void libererTabJeu(Jeu* tJeu[], int* nbElem)
{
	for (int i = 0; i<*nbElem; ++i)
	{
		free(tJeu[i]);
		tJeu[i] = NULL;
	}
	*nbElem = 0;
}

unsigned int genIdJeu(Jeu* tJeu[], int nbElem)
{
	int i=0;
	while (rechercherJeu(tJeu, nbElem, i) != ERR_NOT_FOUND)
		++i;
	return i;
}

void decalageAGaucheJeu(Jeu* tJeu[], int debut, int nbElem)
{
	for (int i = debut; i < nbElem-1; ++i)
		tJeu[i] = tJeu[i+1];
}

void decalageADroiteJeu(Jeu* tJeu[], int debut, int nbElem)
{
	for (int i = nbElem; i > debut; ++i)
		tJeu[i] = tJeu[i-1];
}

int rechercherJeu(Jeu* tJeu[], int nbElem, unsigned int idJeu)
{
	int i;
	for (i = 0; i < nbElem; ++i)
		if (tJeu[i]->id == idJeu)
			return i;
	return ERR_NOT_FOUND;
}

int retirerJeu(Jeu* tJeu[], int nbElem, unsigned int idJeu)
{
	int rang = rechercherJeu(tJeu, nbElem, idJeu);
	if (rang == ERR_NOT_FOUND)
	{
		printf("Jeu non trouvé\n");
		return nbElem;
	}

	free(tJeu[rang]);
	decalageAGaucheJeu(tJeu, rang, nbElem);

	return nbElem-1;
}


int ajouterJeu(Jeu* tJeu[], int nbElem, Jeu jeu, int nbElemMax)
{
	if (nbElem+1 > nbElemMax)
	{
		fprintf(stderr, "Erreur: taille de tableau de jeu trop petite\n");
		return ERR_OUT_OF_RANGE;
	}

	tJeu[nbElem] = (Jeu*) malloc(sizeof(Jeu));
	if (tJeu[nbElem] == NULL)
	{
		fprintf(stderr, "Erreur: probleme d'allocation\n");
		return ERR_ALLOCATION;
	}
	*tJeu[nbElem] = jeu;

	return nbElem+1;
}



int jeuCmp(Jeu* j1, Jeu* j2, TriSur triSur)
{
	switch (triSur)
	{
		case TRI_ID:
			return j1->id - j2->id;
		
		case TRI_NOM:
			return strcmp(j1->nom, j2->nom);
		
		case TRI_TYPE:
			return strcmp(j1->type, j2->type);
		
		case TRI_NB_EXEMPLAIRE_TOTAL:
			return j1->nbExemplaireTotal - j2->nbExemplaireTotal;

		case TRI_NB_EXEMPLAIRE_DISPO:
			return j1->nbExemplaireDispo - j2->nbExemplaireDispo;
		default:
		{
			fprintf(stderr, "Erreur: cas de comparaison non implementé\n");
			exit(2);
		}
	}

}

void copyTabJeu(Jeu* tSource[], unsigned int debut, unsigned int fin, Jeu* tDest[])
{
	for (unsigned int i = debut; i < fin; ++i)
		tDest[i-debut] = tSource[i];
}

void fusionTabJeu(Jeu* tSource1[], unsigned int nbElem1, Jeu* tSource2[], unsigned int nbElem2, TriSur triSur, Jeu* tDest[])
{
	unsigned int nS1 = 0, nS2 = 0, nD = 0;
	int cmp;
	
	while (nS1 < nbElem1 && nS2 < nbElem2)
	{
		cmp = jeuCmp(tSource1[nS1], tSource2[nS2], triSur);
		if (cmp < 0)
		{
			tDest[nD] = tSource1[nS1];
			++nD;
			++nS1;
		}
		else //Les jeux sont uniques dans la liste donc le cas (cmp == 0) n'est pas sensé se presenter
		{
			tDest[nD] = tSource2[nS2];
			++nD;
			++nS2;
		}
	}

	while (nS1 < nbElem1)
	{
		tDest[nD] = tSource1[nS1];
		++nD;
		++nS1;
	}
	
	while (nS2 < nbElem2)
	{
		tDest[nD] = tSource2[nS2];
		++nD;
		++nS2;
	}
}

//tri tJeu et retourne
void triJeu(Jeu* tJeux[], unsigned int nbElem, TriSur triSur)
{
	unsigned int nb1 = nbElem/2;
	unsigned int nb2 = nbElem - nb1;
	Jeu* t1[nb1];
	Jeu* t2[nb2];

	if (nbElem <= 1)
		return;

	copyTabJeu(tJeux, 0, nb1, t1);
	copyTabJeu(tJeux, nb1, nbElem, t2);

	triJeu(t1, nb1, triSur);
	triJeu(t2, nb2, triSur);

	fusionTabJeu(t1, nb1, t2, nb2, triSur, tJeux);
}