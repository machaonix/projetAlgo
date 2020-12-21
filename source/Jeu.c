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
	fflush(stdout);
	scanf("%c%*c", &choix);
	if (choix == 'O')
		return jeu;

	return jeu;
}

void afficheTabJeu(Jeu* tJeu[], int nbElem, FILE* flux)
{
	if (flux == stdout)
		printf("Id\tType\tExemplaires\tNom\n");
	for (int i = 0; i<nbElem; ++i)
		afficheJeu(Jeu[i], flux);
}

Jeu lireJeu(FILE* flux)
{
	Jeu jeu;
	fscanf(flux, "%d%s%d", &(jeu.id), jeu.type, &(jeu.nbExemplaireTotal));
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
		++i;
	}

	fclose(flux)

	return i;
}