#include "Jeu.h"


/*
		afficheJeu
Description :
	Ecrit differents composants du jeu (en parametre) dans le flux (en parametre)

Arguments :
	Jeu* jeu -> un pointeur sur le jeu à afficher
	FILE* flux -> le flux de sortie sur lequel écrire
*/
void afficheJeu(Jeu* jeu, FILE* flux)
{
	if (flux == stdout)
		fprintf(flux, "%d\t%s\t%d\t%d\t%s", jeu->id, jeu->type, jeu->nbExemplaireTotal, jeu->nbExemplaireDispo, jeu->nom);
	else
		fprintf(flux, "%d\t%s\t%d\t%s", jeu->id, jeu->type, jeu->nbExemplaireTotal, jeu->nom);
}



/*
		allocJeu
Description :
	Alloue la mémoire necessaire à un Jeu
	Cette fonction est l'unique fonction allouant de la mémoire pour un jeu

Valeur de retour :
	Si erreur -> NULL
	Sinon -> un pointeur sur jeu vers l'espace alloué
*/
Jeu* allocJeu(void)
{
	Jeu* jeu = (Jeu*) malloc(sizeof(Jeu));
	if (jeu == NULL)
	{
		fprintf(stderr, "Erreur: Allocation\n");
		return NULL;
	}
	return jeu;
}


/*
		nouvJeu
Description :
	Fonction interactive qui permet à l'utilisateur d'entrer les caracteristques d'un nouveau jeu

Valeur de retour :
	Si erreur -> NULL
	Sinon -> un pointeur vers le jeu nouvellement crée

Arguments :
	unsigned int id -> identifiant du nouveau jeu
*/
Jeu* nouvJeu(unsigned int id)
{
	Jeu* jeu = allocJeu();
	if (jeu == NULL)
		return NULL;

	jeu->id = id;

	printf("Nom du jeu : ");
	fflush(stdout);
	fgets(jeu->nom, 41, stdin);
	jeu->nom[strlen(jeu->nom)-1] = '\0';

	printf("\nType du jeu : ");
	fflush(stdout);
	scanf("%s%*c", jeu->type);

	printf("\nNombre d'exemplaires : ");
	fflush(stdout);
	scanf("%d%*c", &(jeu->nbExemplaireTotal));
	jeu->nbExemplaireDispo = jeu->nbExemplaireTotal;

	return jeu;
}

/*
		lireJeu
Description :
	Lis un jeu dans un flux

Valeur de retour :
	Si erreur -> NULL
	Sinon -> un pointeur sur le jeu lu

Arguments :
	FILE* flux -> un flux d'entrée ou lire le jeu
*/
Jeu* lireJeu(FILE* flux)
{
	Jeu* jeu = allocJeu();
	if (jeu == NULL)
		return NULL;

	fscanf(flux, "%d%s%d%*c", &(jeu->id), jeu->type, &(jeu->nbExemplaireTotal));
	jeu->nbExemplaireDispo = jeu->nbExemplaireTotal;

	fgets(jeu->nom, 41,flux);
	jeu->nom[strlen(jeu->nom)-1] = '\0';
	return jeu;
}


/*
		jeuCmp
Description :
	Compare 2 jeux en fonction d'un de leurs attributs
	Cette fonction "calque" ses valeurs de retour sur celle de strcmp

Valeur de retour (ret) :
	Si j1 < j2 -> ret < 0
	Si j1 == j2 -> ret = 0
	Si j1 > j2 -> ret > 0

Arguments :
	Jeu* j1, Jeu* j2 -> les 2 jeux à comparer
	ElementJeu elementJeu -> Dicte l'attribut à utiliser pour la comparaison
*/
int jeuCmp(Jeu* j1, Jeu* j2, ElementJeu elementJeu)
{
	switch (elementJeu)
	{
		case ELEM_JEU_ID:
			return j1->id - j2->id;

		case ELEM_JEU_NOM:
			return strcmp(j1->nom, j2->nom);

		case ELEM_JEU_TYPE:
			return strcmp(j1->type, j2->type);

		case ELEM_JEU_NB_EXEMPLAIRE_TOTAL:
			return j1->nbExemplaireTotal - j2->nbExemplaireTotal;

		case ELEM_JEU_NB_EXEMPLAIRE_DISPO:
			return j1->nbExemplaireDispo - j2->nbExemplaireDispo;
		default:
		{
			fprintf(stderr, "Erreur: cas de comparaison non implementé\n");
			exit(2);
		}
	}
}




/*
		elementJeuExiste
Description :
	Indique si l'element passé en paramètre existe

Valeur de retour (ret) :
	Si l'element existe -> TRUE
	Sinon -> FALSE

Arguments :
	ElementJeu elementJeu -> L'element à tester
	Bool noneAutorisee -> indique si ELEM_JEU_NONE est considerer comme un element
*/
Bool elementJeuExiste(ElementJeu elementJeu, Bool noneAutorisee)
{
	if (elementJeu == ELEM_JEU_NONE && !noneAutorisee)
		return FALSE;

	switch (elementJeu) {
		case ELEM_JEU_NONE:
		case ELEM_JEU_ID:
		case ELEM_JEU_NOM:
		case ELEM_JEU_TYPE:
		case ELEM_JEU_NB_EXEMPLAIRE_TOTAL:
		case ELEM_JEU_NB_EXEMPLAIRE_DISPO:
			return TRUE;
	}
	return FALSE;
}

/*
		afficheAllElementJeu
Description :
	Affiche tout les ElementJeu (sauf ELEM_JEU_NONE) dans le but d'une selection par l'utilisateur
*/
void afficheAllElementJeu(void)
{
	printf("%d)\tIdentifiant\n", ELEM_JEU_ID);
	printf("%d)\tNom\n", ELEM_JEU_NOM);
	printf("%d)\tCategorie\n", ELEM_JEU_TYPE);
	printf("%d)\tNombre total d'exemplaire\n", ELEM_JEU_NB_EXEMPLAIRE_TOTAL);
	printf("%d)\tNombre disponible d'exemplaire\n", ELEM_JEU_NB_EXEMPLAIRE_DISPO);
}

/*
	choisirElementJeu
Description :
	Permet à l'utilisateur de choisir un ElementJeu

Valeur de retour :
	-> L'element choisi

Arguments :
	char utilite[] -> permet de donner du contexte au choix de l'utilisateur (une action commençant par un verbe à l'infinitif)
*/
ElementJeu choisirElementJeu(char utilite[])
{
	ElementJeu elementJeu;
	printf("Veuillez choisir un element de jeu pour %s\n", utilite);
	afficheAllElementJeu();
	fflush(stdout);
	scanf("%d%*c", (unsigned int*)&elementJeu);
	while (!elementJeuExiste(elementJeu, FALSE))
	{
		printf("Veuillez choisir un element de jeu valide\n");
		fflush(stdout);
		scanf("%d%*c", (unsigned int*)&elementJeu);
	}

	return elementJeu;
}

/*
		entrerValeurElementJeu
Description :
	Permet de lire une valeur specifique d'un jeu

Valeur de retour
	-> Un CodeErreur

Arguments :
	Jeu* jeu -> le jeu dans lequel ecrire
	ElementJeu elementJeu -> Indique la variable à modifier
*/
CodeErreur entrerValeurElementJeu(Jeu* jeu, ElementJeu elementJeu)
{
	switch (elementJeu) {
	case ELEM_JEU_NONE:
		printf("Erreur imposible de lire un element non existant\n");
		return ERR_OPERATION_INVALIDE;
	case ELEM_JEU_ID:
		printf("Veuillez entrer l'id du jeu\n");
		fflush(stdout);
		scanf("%u%*c", &jeu->id);
		break;
	case ELEM_JEU_NOM:
		printf("Veuillez entrer le nom du jeu\n");
		fflush(stdout);
		fgets(jeu->nom, 41,stdin);
		jeu->nom[strlen(jeu->nom)-1] = '\0';
		break;
	case ELEM_JEU_TYPE:
		printf("Veuillez entrer la categorie du jeu\n");
		fflush(stdout);
		scanf("%s%*c", jeu->type);
		break;
	case ELEM_JEU_NB_EXEMPLAIRE_TOTAL:
		printf("Veuillez entrer le nombre d'exemplaire total du jeu\n");
		fflush(stdout);
		scanf("%u%*c", &jeu->nbExemplaireTotal);
		break;
	case ELEM_JEU_NB_EXEMPLAIRE_DISPO:
		printf("Veuillez entrer le nombre d'exemplaire disponible du jeu\n");
		fflush(stdout);
		scanf("%u%*c", &jeu->nbExemplaireDispo);
		break;
	}

	return ERR_NO_ERR;
}

/*
		copyJeu
Description :
	Copie un jeu source dans un jeu destination
	Cette fonction est à utiliser à la place d'un "jd = js" car les jeux ont des pointeurs parmis leur attributs

Arguments :
	Jeu* js -> jeu dont le contenu sera copié
	Jeu* jd -> jeu dans lequel sera collé le contenu de js
*/
void copyJeu(Jeu* jd, Jeu* js)
{
	jd->id = js->id;
	jd->nbExemplaireTotal = js->nbExemplaireTotal;
	jd->nbExemplaireDispo = js->nbExemplaireDispo;

	strcpy(jd->nom, js->nom);
	strcpy(jd->type, js->type);
}
