#include "Jeu.h"



void afficheJeu(Jeu* jeu, FILE* flux)
{
	fprintf(flux, "%d\t%s\t%d\t%s", jeu->id, jeu->type, jeu->nbExemplaireTotal, jeu->nom);
}

Jeu nouvJeu(unsigned int id)
{
	Jeu jeu;
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

	return jeu;
}


Jeu lireJeu(FILE* flux)
{
	Jeu jeu;
	fscanf(flux, "%d%s%d%*c", &(jeu.id), jeu.type, &(jeu.nbExemplaireTotal));
	fgets(jeu.nom, 41,flux);
	jeu.nom[strlen(jeu.nom)-1] = '\0';
	return jeu;
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

