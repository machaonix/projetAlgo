#include "TableauJeu.h"


void initTabJeu(TableauJeu* tabJeu)
{
	for (int i = 0; i< TAILLE_MAX_TAB_JEU; ++i)
	{
		tabJeu->jeux[i] = NULL;
	}
	tabJeu->nbElement = 0;
	tabJeu->triSur = TRI_NON_TRIE;
}


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

		if (jeu == NULL) return ERR_ALLOCATION;

		tabJeu->jeux[tabJeu->nbElement] = jeu;
		tabJeu->nbElement++;
		
		jeu = lireJeu(flux);
	}

	fclose(flux);

	return 0;
}

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

void libererTabJeu(TableauJeu* tabJeu)
{
	for (unsigned int i = 0; i<tabJeu->nbElement; ++i)
	{
		free(tabJeu->jeux[i]);
		tabJeu->jeux[i] = NULL;
	}
	tabJeu->nbElement = 0;
}


Bool jeuDisponible(TableauJeu* tabJeu, unsigned int id)
{
	Bool trouve;
	unsigned int rang = rechercherIdJeu(tabJeu, id, &trouve);
	if (trouve)
		if (tabJeu->jeux[rang]->nbExemplaireDispo>0)
			return TRUE;
	return FALSE;
}

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


int _rechercherIdJeu_TabNonTrie(TableauJeu* tabJeu, unsigned int idJeu)
{
	unsigned int i;
	for (i = 0; i < tabJeu->nbElement; ++i)
		if (tabJeu->jeux[i]->id == idJeu)
			return i;
	return ERR_NOT_FOUND;
}


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

	return ERR_NO_ERR;
}

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

void _decalageAGaucheJeu(TableauJeu* tabJeu, unsigned int debut)
{
	for (unsigned int i = debut; i < tabJeu->nbElement-1; ++i)
		tabJeu->jeux[i] = tabJeu->jeux[i+1];
}

void _decalageADroiteJeu(TableauJeu* tabJeu, unsigned int debut)
{
	unsigned int i;
	for (i = tabJeu->nbElement; i > debut; --i)
		tabJeu->jeux[i] = tabJeu->jeux[i-1];
}


unsigned int genIdJeu(TableauJeu* tabJeu)
{
	Bool trouve;
	unsigned int i=0;
	rechercherIdJeu(tabJeu, tabJeu->nbElement, &trouve);
	if (trouve == FALSE)
	{
		return tabJeu->nbElement;
	}
	
	rechercherIdJeu(tabJeu, i, &trouve);

	while (trouve == TRUE)
	{
		++i;
		rechercherIdJeu(tabJeu, i, &trouve);
	}
	return i;
}


//tri tabJeu selon triSur
void triTabJeu(TableauJeu* tabJeu, TriSur triSur)
{
	_triJeu(tabJeu->jeux, tabJeu->nbElement, triSur);

	tabJeu->triSur = triSur;
}


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
