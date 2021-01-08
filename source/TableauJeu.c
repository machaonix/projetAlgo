#include "TableauJeu.h"


/*
		initTabJeu
Description :
	Initialise les attributs du TableauJeu passé en paramètre

Argument :
	TableauJeu* tabJeu -> un pointeur sur le tableau à initialiser
*/
void initTabJeu(TableauJeu* tabJeu)
{
	for (int i = 0; i< TAILLE_MAX_TAB_JEU; ++i)
	{
		tabJeu->jeux[i] = NULL;
	}
	tabJeu->nbElement = 0;
	tabJeu->triSur = ELEM_JEU_NONE;
}



void affichePartieTabJeu(TableauJeu* tabJeu, unsigned int begin, unsigned int end, FILE* flux)
{
	if (flux == stdout)
		printf("\nId\tType\tNombre\tDispo\tNom\n");

	for (; begin<tabJeu->nbElement && begin<end; ++begin)
	{
		afficheJeu(tabJeu->jeux[begin], flux);
		fprintf(flux, "\n");
	}
}
/*
		afficheTabJeu
Description :
	Ecrit tout les jeux du tableau sur le flux de sortie donné et une entête si le flux est la sortie standard

Arguments :
	TableauJeu* tabJeu -> Le tableau contenant les jeux à afficher
	FILE* flux -> Le flux de sortie ou écrire
*/
void afficheTabJeu(TableauJeu* tabJeu, FILE* flux)
{
	affichePartieTabJeu(tabJeu, 0, tabJeu->nbElement, flux);
}

/*
		chargerTabJeu
Description :
	Charge dans le tableau de jeux les jeux présents dans le fichier dont le nom est passé en argument

Valeur de retour :
	Si erreur -> le code erreur correspondant
	Sinon -> ERR_NO_ERR

Arguments :
	TableauJeu* tabJeu -> Le tableau dans lequel charger le fichier
	char nomFichier[] -> Le chemin du fichier à charger
*/
CodeErreur chargerTabJeu(TableauJeu* tabJeu, char nomFichier[])
{
	FILE* flux;
	Jeu* jeu;

	if (tabJeu->nbElement != 0)
		libererTabJeu(tabJeu);


	tabJeu->triSur = ELEM_JEU_NONE;

	flux = fopen(nomFichier, "r");
	if (!flux)
	{
		fprintf(stderr, "Erreur: ouverture fichier\n");
		return ERR_OUVERTURE_FICHIER;
	}

	jeu = lireJeu(flux);
	while(!feof(flux))
	{

		if (tabJeu->nbElement==TAILLE_MAX_TAB_JEU)
		{
			fprintf(stderr, "Erreur: taille de tableau de jeu trop petite\n");
			fclose(flux);
			return ERR_OUT_OF_RANGE;
		}

		if (jeu == NULL)
		{
			fclose(flux);
			return ERR_ALLOCATION;
		}

		tabJeu->jeux[tabJeu->nbElement] = jeu;
		tabJeu->nbElement++;

		jeu = lireJeu(flux);
	}

	fclose(flux);

	return ERR_NO_ERR;
}

/*
		sauvegarderTabJeu
Description :
	Sauvegarde le tableau de jeu dans un fichier

Valeur de retour :
	Si erreur -> le code erreur correspondant
	Sinon -> ERR_NO_ERR

Arguments :
	TableauJeu* tabJeu -> Le tableau a sauvegarder
	char nomFichier[] -> Le chemin du fichier crée/ecraser pour sauvegarder le tableau
*/
CodeErreur sauvegarderTabJeu(TableauJeu* tabJeu, char nomFichier[])
{
	FILE* flux = NULL;

	flux = fopen(nomFichier, "w");
	if (flux == NULL)
	{
		fprintf(stderr, "Erreur: ouverture fichier\n");fflush(stderr);
		return ERR_OUVERTURE_FICHIER;
	}

	afficheTabJeu(tabJeu, flux);

	fclose(flux);

	return ERR_NO_ERR;
}

/*
		libererTabJeu
Description :
	Libere la mémoire allouée par un tableau de jeu

Arguments :
	TableauJeu* tabJeu -> Le tableau à liberer
*/
void libererTabJeu(TableauJeu* tabJeu)
{
	for (unsigned int i = 0; i<tabJeu->nbElement; ++i)
	{
		free(tabJeu->jeux[i]);
		tabJeu->jeux[i] = NULL;
	}
	tabJeu->nbElement = 0;
}

/*
		jeuDisponible
Description :
	Indique si un jeu est disponible ou non

Valeur de retour :
	Si le jeu existe et à un nombre d'exemplaire > 0 -> TRUE
	Sinon -> FALSE

Arguments :
	TableauJeu* tabJeu -> Le tableau dans lequel le jeu est stocké
	Jeu* jeu -> le jeu en question (doit avoir l'id de defini)
*/
Bool jeuDisponible(TableauJeu* tabJeu, Jeu* jeu)
{
	Bool trouve = TRUE;
	unsigned int rang = rechercherJeu(tabJeu, jeu, ELEM_JEU_ID, &trouve, TRUE);

	if (trouve == TRUE)
	{
		if (tabJeu->jeux[rang]->nbExemplaireDispo>0)
			return TRUE;
	}

	return FALSE;
}



CodeErreur rechercherJeuInteractif(TableauJeu* tabJeu, Bool* trouve, unsigned int* rang)
{
	Jeu jeuARechercher;
	unsigned int rangInf;
	unsigned int rangSup;
	CodeErreur cErr;
	ElementJeu elementJeu = choisirElementJeu("rechercher votre jeu");


	cErr =  entrerValeurElementJeu(&jeuARechercher, elementJeu);
	if (cErr != ERR_NO_ERR)
	{
		printf("Erreur operation avortée\n");
		return cErr;
	}

	triTabJeu(tabJeu, elementJeu);

	rangInf = rechercherJeu(tabJeu, &jeuARechercher, elementJeu, trouve, TRUE);

//permet de trouver en tapant le début du mot recherché
	if (elementJeu == ELEM_JEU_TYPE)
		jeuARechercher.type[strlen(jeuARechercher.type)-1] += 1;
	if (elementJeu == ELEM_JEU_NOM)
		jeuARechercher.nom[strlen(jeuARechercher.nom)-1] += 1;

	//Les id de jeu sont uniques
	if (elementJeu == ELEM_JEU_ID)
	{
		*rang = rangInf;
		if (*trouve)
		{
			afficheJeu(tabJeu->jeux[*rang], stdout);
			if (!IO_Choix_O_N("\nLe jeu si dessus est-il le jeu recherché"))
				*trouve = FALSE;
		}
		else
			printf("Jeu non trouvé\n");
		return ERR_NO_ERR;
	}
		return

	rangSup = rechercherJeu(tabJeu, &jeuARechercher, elementJeu, trouve, FALSE);

	if (rangInf <= rangSup)
	{
		affichePartieTabJeu(tabJeu, rangInf, rangSup+1, stdout);

		printf("Veuillez maintenant indiquer l'identifiant du jeu : ");
		fflush(stdout);
		scanf("%u%*c", &jeuARechercher.id);

		*rang = rechercherJeu(tabJeu, &jeuARechercher, ELEM_JEU_ID, trouve, TRUE);
		if (*trouve == FALSE)
		{
			printf("L'identifiant que vous avez entré n'est pas referencé\n");
		}
		return ERR_NO_ERR;
	}
	else
	{
		printf("Jeu non trouvé\n");
		return ERR_NO_ERR;
	}
}


/*
		rechercherJeu
Description :
	Recherche un jeu dans un tableau de jeu

Valeur de retour :
	-> Le rang d'insertion ou le rang ou le jeu est

Arguments :
	TableauJeu* tabJeu -> Le tableau de jeu où rechercher
	unsigned int idJeu -> L'identifiant recherché
	Bool* trouve -> Si le jeu est trouvé est assigné à TRUE sinon FALSE
*/
unsigned int rechercherJeu(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve, Bool cherchePremier)
{
	unsigned int rang;
	if (tabJeu->triSur != elementJeu)
	{
		if (cherchePremier)
			rang = _rechercherPremierJeu_TabNonTrie(tabJeu, jeu, elementJeu, trouve);
		else
			rang = _rechercherDernierJeu_TabNonTrie(tabJeu, jeu, elementJeu, trouve);

		return rang;
	}

	if (cherchePremier)
		rang =_rechercherPremierJeu_TabTrie(tabJeu, jeu, elementJeu, trouve);
	else
		rang =_rechercherDernierJeu_TabTrie(tabJeu, jeu, elementJeu, trouve);
	return rang;
}


/*
		_rechercherJeu_TabNonTrie
Description :
	/!\ Cette fonction n'a pas vocation à être utilisée par une autre fonction que rechercherIdJeu /!\
	Elle recherche un jeu dans un tableau de jeu non trié en itérant sur tout les elements

Valeur de retour :
	Si trouvé -> le rang du jeu
	Sinon -> le rang d'insertion

Arguments :
	TableauJeu* tabJeu -> Le tableau dans lequel rechercher
	Jeu* jeu -> Le jeu à rechercher
	ElementJeu elementJeu -> L'element par rapport auquel rechercher
	Bool* trouve -> Si le jeu est trouvé est assigné à TRUE sinon FALSE
*/
unsigned int _rechercherPremierJeu_TabNonTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve)
{
	unsigned int i;
	for (i = 0; i < tabJeu->nbElement; ++i)
		if (jeuCmp(tabJeu->jeux[i], jeu, elementJeu) == 0)
		{
			*trouve = TRUE;
			return i;
		}

	*trouve = FALSE;
	return i;
}

unsigned int _rechercherDernierJeu_TabNonTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve)
{
	unsigned int i;
	for (i = tabJeu->nbElement-1; i > 0 ; --i)
		if (jeuCmp(tabJeu->jeux[i], jeu, elementJeu) == 0)
		{
			*trouve = TRUE;
			return i;
		}

	*trouve = FALSE;
	return i;
}


/*
		_rechercherJeu_TabTrie
Description :
	/!\ Cette fonction n'a pas vocation à être utilisée par une autre fonction que rechercherIdJeu /!\
	Elle recherche un jeu dans un tableau de jeu trié par l'element donnee par dichotomie

Valeur de retour :
	Si trouvé -> le rang du jeu
	Sinon -> le rang d'insertion

Arguments :
	TableauJeu* tabJeu -> Le tableau dans lequel rechercher
	Jeu* jeu -> Le jeu à rechercher
	ElementJeu elementJeu -> L'element par rapport auquel rechercher
	Bool* trouve -> Si le jeu est trouvé est assigné à TRUE sinon FALSE
*/
unsigned int _rechercherPremierJeu_TabTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve)
{
	int inf = 0, sup = tabJeu->nbElement-1;
	int mil = (inf + sup)/2;
	*trouve = FALSE;

	while (inf <= sup)
	{
		int comparaison = jeuCmp(tabJeu->jeux[mil], jeu, elementJeu);
		if (comparaison == 0)
			*trouve = TRUE;

		if (comparaison >= 0)
			sup = mil-1;
		else
			inf = mil +1;

		mil = (inf + sup)/2;
	}

	return inf;
}

unsigned int _rechercherDernierJeu_TabTrie(TableauJeu* tabJeu, Jeu* jeu, ElementJeu elementJeu, Bool* trouve)
{
	int inf = 0, sup = tabJeu->nbElement-1;
	int mil = (inf + sup)/2;
	*trouve = FALSE;

	while (inf <= sup)
	{
		int comparaison = jeuCmp(tabJeu->jeux[mil], jeu, elementJeu);
		if (comparaison == 0)
			*trouve = TRUE;

		if (comparaison <= 0)
			inf = mil+1;
		else
			sup = mil-1;

		mil = (inf + sup)/2;
	}

	if (sup<0)
		return 0;
	return sup;
}

/*
		retirerJeu
Description :
	Retire le jeu correspondant à l'id donné du tableau de jeux

Valeur de retour :
	Si pas d'erreur -> ERR_NO_ERR
	Sinon -> Le code erreur correspondant

Arguments :
	TableauJeu* tabJeu -> Le tableau duquel on veut retirer le jeu
	unsigned int idJeu -> L'identifiant du jeu que l'on veut retirer
*/
CodeErreur retirerJeu(TableauJeu* tabJeu, Jeu* jeu)
{
	Bool trouve;
	unsigned int rang = rechercherJeu(tabJeu, jeu, ELEM_JEU_ID, &trouve, TRUE);
	if (trouve == FALSE)
		return ERR_NOT_FOUND;

	free(tabJeu->jeux[rang]);
	_decalageAGaucheJeu(tabJeu, rang);

	--(tabJeu->nbElement);

	return ERR_NO_ERR;
}

/*
		retirerJeuInteractif
Description :
	Fonction interactive permettant de retirer un jeu du tableau
	Appelle la fonction retirerJeu

Valeur de retour :
	Si pas d'erreur -> ERR_NO_ERR
	Sinon -> Le code erreur correspondant

Arguments :
	TableauJeu* tabJeu -> Le tableau duquel on veut retirer le jeu
*/
CodeErreur retirerJeuInteractif(TableauJeu* tabJeu)
{
	unsigned int rangJeu;
	Bool trouve;
	Jeu* jeuARetirer;
	CodeErreur cErr;

	cErr = rechercherJeuInteractif(tabJeu, &trouve, &rangJeu);
	if (cErr != ERR_NO_ERR)
		return cErr;

	if (trouve == FALSE)
		return ERR_NOT_FOUND;

	jeuARetirer = tabJeu->jeux[rangJeu];

	cErr = retirerJeu(tabJeu, jeuARetirer);
	if (cErr == ERR_NOT_FOUND)
	{
		printf("Jeu non trouvé\n");
		fflush(stdout);
		return ERR_OPERATION_INVALIDE;
	}

	printf("Jeu retiré\n");
	fflush(stdout);
	return ERR_NO_ERR;
}



/*
		ajouterJeu
Description :
	Ajoute le jeu donné au tableau de jeux

Valeur de retour :
	Si pas d'erreur -> ERR_NO_ERR
	Sinon -> Le code erreur correspondant

Arguments :
	TableauJeu* tabJeu -> Le tableau auquel on veut ajouter le jeu
	Jeu* jeu -> Le jeu que l'on veut ajouter
*/
CodeErreur ajouterJeu(TableauJeu* tabJeu, Jeu* jeu)
{
	Bool trouve;
	unsigned int rangInser;

	if (tabJeu->nbElement >= TAILLE_MAX_TAB_JEU)
	{
		fprintf(stderr, "Erreur: taille de tableau de jeu trop petite\n");
		return ERR_OUT_OF_RANGE;
	}

	if (tabJeu->triSur != ELEM_JEU_NONE)
		rangInser = rechercherJeu(tabJeu, jeu, tabJeu->triSur, &trouve, TRUE);
	else
		rangInser = rechercherJeu(tabJeu, jeu, ELEM_JEU_ID, &trouve, TRUE);

	if (trouve == TRUE)
	{
		printf("Jeu existant, imposible de l'ajouter\n");
		return ERR_OPERATION_INVALIDE;
	}

	_decalageADroiteJeu(tabJeu, rangInser);

	tabJeu->jeux[rangInser] = jeu;
	tabJeu->nbElement++;

	return ERR_NO_ERR;
}


/*
		ajouterJeuInteractif
Description :
	Fonction interactive permettant d'aujouter un jeu au tableau
	Appelle la fonction ajouterJeu

Valeur de retour :
	Si pas d'erreur -> ERR_NO_ERR
	Sinon -> Le code erreur correspondant

Arguments :
	TableauJeu* tabJeu -> Le tableau auquel on veut ajouter le jeu
*/
CodeErreur ajouterJeuInteractif(TableauJeu* tabJeu)
{
	CodeErreur cErr;
	Jeu* jeu = nouvJeu(genIdJeu(tabJeu));
	if (jeu == NULL) return ERR_ALLOCATION;
	afficheJeu(jeu, stdout);

	if (IO_Choix_O_N("\nSouhaitez vous ajouter le jeu ci dessus"))
	{
		cErr = ajouterJeu(tabJeu, jeu);
		if (cErr == 0)
			printf("Jeu ajouté\n");
		fflush(stdout);
		return cErr;
	}

	return ERR_NO_ERR;
}

/*
		_decalageAGaucheJeu
Description :
	/!\ Cette fonction n'a pas vocation à être utilisée par des fonctions exterieurs à ce fichier car cette fontion ne fait pas de verification de bon fonctionnement /!\
	Decale vers la "gauche" les jeux du tableau en ecrasant le jeu du rang debut

Arguments :
	TableauJeu* tabJeu -> Le tableau a "décaler"
	unsigned int debut -> le rang a partir duquel décaler
*/
void _decalageAGaucheJeu(TableauJeu* tabJeu, unsigned int debut)
{
	for (unsigned int i = debut; i < tabJeu->nbElement-1; ++i)
		tabJeu->jeux[i] = tabJeu->jeux[i+1];
}


/*
		_decalageADroiteJeu
Description :
	/!\ Cette fonction n'a pas vocation à être utilisée par des fonctions exterieurs à ce fichier car cette fontion ne fait pas de verification de bon fonctionnement/!\
	Decale vers la "droite" les jeux du tableau

Arguments :
	TableauJeu* tabJeu -> Le tableau a "décaler"
	unsigned int debut -> le rang a partir duquel décaler
*/
void _decalageADroiteJeu(TableauJeu* tabJeu, unsigned int debut)
{
	unsigned int i;
	for (i = tabJeu->nbElement; i > debut; --i)
		tabJeu->jeux[i] = tabJeu->jeux[i-1];
}

/*
		genIdJeu
Description :
	Recherche et retourne un identifiant non utilisé
	Cette fonction considere qu'il existe au moins un identifiant libre

Valeur de retour :
	Retourne un identifiant libre

Arguments :
	TableauJeu* tabJeu -> Le tableau pour lequel trouver un identifiant libre
*/
unsigned int genIdJeu(TableauJeu* tabJeu)
{
	Bool trouve;
	Jeu jeuIncomplet;
	jeuIncomplet.id = tabJeu->nbElement;
	rechercherJeu(tabJeu, &jeuIncomplet, ELEM_JEU_ID, &trouve, TRUE);
	if (trouve == FALSE)
	{
		return tabJeu->nbElement;
	}

	jeuIncomplet.id = 0;
	//si il existe un jeu avec l'identifiant egal au nombre d'elements, un des identifiants inferieur est libre
	rechercherJeu(tabJeu, &jeuIncomplet, ELEM_JEU_ID, &trouve, TRUE);

	while (trouve == TRUE)
	{
		++jeuIncomplet.id;
		rechercherJeu(tabJeu, &jeuIncomplet, ELEM_JEU_ID, &trouve, TRUE);
	}
	return jeuIncomplet.id;
}



void triTabJeuInteractif(TableauJeu* tabJeu)
{
	ElementJeu elementJeu = choisirElementJeu("trier votre tableau de jeu");
	triTabJeu(tabJeu, elementJeu);
}

/*
		triTabJeu
Description :
	Tri le tableau de jeu en fonction de elementJeu
	Encapsule la fonction _triJeu

Arguments :
	TableauJeu* tabJeu -> Tableau à trier
	ElementJeu elementJeu -> Maniere de trier
*/
void triTabJeu(TableauJeu* tabJeu, ElementJeu elementJeu)
{
	if (elementJeu == ELEM_JEU_NONE)
	{
		fprintf(stderr, "Erreur operation invalide : trier avec ELEM_JEU_NONE\n");
		exit(-ERR_OPERATION_INVALIDE);
	}

	if (tabJeu->triSur == elementJeu)
		return;

	_triJeu(tabJeu->jeux, tabJeu->nbElement, elementJeu);

	tabJeu->triSur = elementJeu;
}


/*
		_triJeu
Description :
	/!\ Cette fonction utilise un tableau de jeu nu, ne pas l'utiliser directement -> passer par triTabJeu et utilisez un TableauJeu /!\
	Tri le tableau de jeu en fonction de elementJeu

Arguments :
	Jeu* tJeu[] -> Tableau à trier
	unsigned int nbElement -> nombre d'element du tableau
	ElementJeu elementJeu -> Maniere de trier
*/
void _triJeu(Jeu* tJeu[], unsigned int nbElement, ElementJeu elementJeu)
{
	unsigned int nb1 = nbElement/2;
	unsigned int nb2 = nbElement - nb1;
	Jeu* t1[nb1];
	Jeu* t2[nb2];

	if (nbElement <= 1)
		return;

	copyTabJeu(tJeu, 0, nb1, t1);
	copyTabJeu(tJeu, nb1, nbElement, t2);

	_triJeu(t1, nb1, elementJeu);
	_triJeu(t2, nb2, elementJeu);

	fusionTabJeu(t1, nb1, t2, nb2, elementJeu, tJeu);
}


/*
		copyTabJeu
Description :
	/!\ Cette fonction utilise un tableau de jeu nu, ne pas l'utiliser directement /!\
	Copie la partie du tableau source designé dans le tableau de destination

Arguments :
	Jeu* tSource[] -> tableau source
	unsigned int debut -> rang de début de la copie (inclu)
	unsigned int fin -> rang d'arret de la copie (exclu)
	Jeu* tDest[] -> tableau de destination
*/
void copyTabJeu(Jeu* tSource[], unsigned int debut, unsigned int fin, Jeu* tDest[])
{
	for (unsigned int i = debut; i < fin; ++i)
		tDest[i-debut] = tSource[i];
}

/*
		fusionTabJeu
Description :
	Fusionne les tableaux sources dans le tableau destination en respectant l'ordre indiqué par elementJeu

Arguments :
	Jeu* tSource1[] -> Tableau source 1
	unsigned int nbElem1 -> nombre d'elements du tableau source 1
	Jeu* tSource2[] -> Tableau source 2
	unsigned int nbElem2 -> nombre d'elements du tableau source 2
	ElementJeu elementJeu -> Maniere de determiner l'ordre des jeux
	Jeu* tDest[] -> Tableau de destination
*/
void fusionTabJeu(Jeu* tSource1[], unsigned int nbElem1, Jeu* tSource2[], unsigned int nbElem2, ElementJeu elementJeu, Jeu* tDest[])
{
	unsigned int nS1 = 0, nS2 = 0, nD = 0;
	int cmp;

	while (nS1 < nbElem1 && nS2 < nbElem2)
	{
		cmp = jeuCmp(tSource1[nS1], tSource2[nS2], elementJeu);
		if (cmp < 0)
		{
			tDest[nD] = tSource1[nS1];
			++nD;
			++nS1;
		}
		else
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
