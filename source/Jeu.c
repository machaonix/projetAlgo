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
