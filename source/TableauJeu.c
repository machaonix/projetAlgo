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
	tabJeu->triSur = TRI_NON_TRIE;
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
	unsigned int i;
	if (flux == stdout)
		printf("\nId\tType\tNombre\tDispo\tNom\n");
	
	for (i = 0; i<tabJeu->nbElement; ++i)
	{
		afficheJeu(tabJeu->jeux[i], flux);
		fprintf(flux, "\n");
	}
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
	

	tabJeu->triSur = TRI_NON_TRIE;

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
	unsigned int id -> l'identifiant du jeu en question
*/
Bool jeuDisponible(TableauJeu* tabJeu, unsigned int id)
{
	Bool trouve;
	unsigned int rang = rechercherIdJeu(tabJeu, id, &trouve);
	if (trouve)
		if (tabJeu->jeux[rang]->nbExemplaireDispo>0)
			return TRUE;
	return FALSE;
}

/*
		rechercherIdJeu
Description :
	Recherche un jeu par son Identifiant dans un tableau de jeu

Valeur de retour :
	-> Le rang d'insertion ou le rang ou le jeu est

Arguments :
	TableauJeu* tabJeu -> Le tableau de jeu où rechercher
	unsigned int idJeu -> L'identifiant recherché
	Bool* trouve -> Si le jeu est trouvé est assigné à TRUE sinon FALSE
*/
unsigned int rechercherIdJeu(TableauJeu* tabJeu, unsigned int idJeu, Bool* trouve)
{
	int rang;
	if (tabJeu->triSur != TRI_ID)
	{
		rang = _rechercherIdJeu_TabNonTrie(tabJeu, idJeu);
		if (rang == ERR_NOT_FOUND)
		{
			*trouve = FALSE;
			return tabJeu->nbElement;
		}
		*trouve = TRUE;
		return rang;
	}	

	return _rechercherIdJeu_TabTriId(tabJeu, idJeu, trouve);
}

/*
		_rechercherIdJeu_TabNonTrie
Description :
	/!\ Cette fonction n'a pas vocation à être utilisée par une autre fonction que rechercherIdJeu /!\
	Elle recherche un identifiant dans un tableau de jeu non trié en itérant sur tout les elements

Valeur de retour :
	Si trouvé -> le rang du jeu
	Sinon -> ERR_NOT_FOUND

Arguments :
	TableauJeu* tabJeu -> Le tableau dans lequel rechercher
	unsigned int idJeu -> L'identifiant à rechercher
*/
int _rechercherIdJeu_TabNonTrie(TableauJeu* tabJeu, unsigned int idJeu)
{
	unsigned int i;
	for (i = 0; i < tabJeu->nbElement; ++i)
		if (tabJeu->jeux[i]->id == idJeu)
			return i;
	return ERR_NOT_FOUND;
}


/*
		_rechercherIdJeu_TabTriId
Description :
	/!\ Cette fonction n'a pas vocation à être utilisée par une autre fonction que rechercherIdJeu /!\
	Elle recherche un identifiant dans un tableau de jeu trié par identifiant par dichotomie

Valeur de retour :
	Si trouvé -> le rang du jeu
	Sinon -> le rang d'insertion

Arguments :
	TableauJeu* tabJeu -> Le tableau dans lequel rechercher
	unsigned int idJeu -> L'identifiant à rechercher
	Bool* trouve -> Si le jeu est trouvé est assigné à TRUE sinon FALSE
*/
unsigned int _rechercherIdJeu_TabTriId(TableauJeu* tabJeu, unsigned int idJeu, Bool* trouve)
{
	unsigned int inf = 0, sup = tabJeu->nbElement-1;
	unsigned int mil = (inf + sup)/2;

	while (inf <= sup)
	{
		if (tabJeu->jeux[mil]->id == idJeu)
		{
			*trouve = TRUE;
			return mil;
		}
		else if (tabJeu->jeux[mil]->id > idJeu)
			sup = mil-1;
		else 
			inf = mil+1;
		mil = (inf + sup)/2;
	}  

	*trouve = FALSE;
	return inf;
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
CodeErreur retirerJeu(TableauJeu* tabJeu, unsigned int idJeu)
{
	Bool trouve;
	unsigned int rang = rechercherIdJeu(tabJeu, idJeu, &trouve);
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
	unsigned int idJeu;
	CodeErreur cErr;

	printf("\nQuel est l'Identifiant du jeu que vous souhaitez retirer ? ");
	fflush(stdout);
	scanf("%d", &idJeu);

	cErr = retirerJeu(tabJeu, idJeu);
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

	rangInser = rechercherIdJeu(tabJeu, jeu->id, &trouve);
	if (trouve == TRUE)
	{
		printf("Jeu existant, imposible de l'ajouter\n");
		return ERR_OPERATION_INVALIDE;
	}

	_decalageADroiteJeu(tabJeu, rangInser);

	tabJeu->jeux[rangInser] = jeu;
	tabJeu->nbElement++;

	if (tabJeu->triSur != TRI_ID)
		tabJeu->triSur = TRI_NON_TRIE;

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
	char choix = 'a';
	Jeu* jeu = nouvJeu(genIdJeu(tabJeu));
	if (jeu == NULL) return ERR_ALLOCATION;

	printf("\nSouhaitez vous ajouter le jeu suivant (O / N) : \n");
	afficheJeu(jeu, stdout);
	printf("\n");
	fflush(stdout);


	while (TRUE)
	{
		scanf("%c%*c",&choix);
		switch (choix)
		{
			case 'O':
			{
				cErr = ajouterJeu(tabJeu, jeu);
				if (cErr == 0)
					printf("Jeu ajouté\n");
				fflush(stdout);
				return cErr;
			}
			case 'N':
			{
				return ERR_NO_ERR;
			}
			default:
			{
				printf("Veuillez répondre par O ou N \n");
				fflush(stdout);
				break;
			}
		}
	}	
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
	unsigned int i=0;
	rechercherIdJeu(tabJeu, tabJeu->nbElement, &trouve);
	if (trouve == FALSE)
	{
		return tabJeu->nbElement;
	}
	
	//si il existe un jeu avec l'identifiant egal au nombre d'elements, un des identifiants inferieur est libre
	rechercherIdJeu(tabJeu, i, &trouve);

	while (trouve == TRUE)
	{
		++i;
		rechercherIdJeu(tabJeu, i, &trouve);
	}
	return i;
}


/*
		triTabJeu
Description :
	Tri le tableau de jeu en fonction de triSur
	Encapsule la fonction _triJeu

Arguments :
	TableauJeu* tabJeu -> Tableau à trier
	TriSur triSur -> Maniere de trier
*/
void triTabJeu(TableauJeu* tabJeu, TriSur triSur)
{
	if (triSur == TRI_NON_TRIE)
	{
		fprintf(stderr, "Erreur operation invalide : trier avec TRI_NON_TRIE\n");
		exit(-ERR_OPERATION_INVALIDE);
	}

	if (tabJeu->triSur == triSur)
		return;

	_triJeu(tabJeu->jeux, tabJeu->nbElement, triSur);

	tabJeu->triSur = triSur;
}


/*
		_triJeu
Description :
	/!\ Cette fonction utilise un tableau de jeu nu, ne pas l'utiliser directement -> passer par triTabJeu et utilisez un TableauJeu /!\
	Tri le tableau de jeu en fonction de triSur

Arguments :
	Jeu* tJeu[] -> Tableau à trier
	unsigned int nbElement -> nombre d'element du tableau
	TriSur triSur -> Maniere de trier
*/
void _triJeu(Jeu* tJeu[], unsigned int nbElement, TriSur triSur)
{
	unsigned int nb1 = nbElement/2;
	unsigned int nb2 = nbElement - nb1;
	Jeu* t1[nb1];
	Jeu* t2[nb2];

	if (nbElement <= 1)
		return;

	copyTabJeu(tJeu, 0, nb1, t1);
	copyTabJeu(tJeu, nb1, nbElement, t2);

	_triJeu(t1, nb1, triSur);
	_triJeu(t2, nb2, triSur);

	fusionTabJeu(t1, nb1, t2, nb2, triSur, tJeu);
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
	Fusionne les tableaux sources dans le tableau destination en respectant l'ordre indiqué par triSur

Arguments :
	Jeu* tSource1[] -> Tableau source 1
	unsigned int nbElem1 -> nombre d'elements du tableau source 1
	Jeu* tSource2[] -> Tableau source 2
	unsigned int nbElem2 -> nombre d'elements du tableau source 2
	TriSur triSur -> Maniere de determiner l'ordre des jeux
	Jeu* tDest[] -> Tableau de destination
*/
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
