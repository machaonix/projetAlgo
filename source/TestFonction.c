#include "TestFonction.h"
/*
void testFonctionDate(void)
{
	Date d1 = {31, 12, 2020};
	Date d2 = {1, 1, 2020};

	for(int i=1; i<=12; ++i)
		{
			d2.mois = i;
			printf("%d\n", dateCmp(d1, d2));
		}
	afficherDate(d1, stdout);
}

void testFonctionAdherant(void)
{
	FILE *f = fopen("../donnee/adherant.don", "r");
	if(f == NULL)
	{
		fprintf(stderr, "Erreur dans l'ouverture du fichier d'adherant\n");
		return;
	}

	Adherant ad = lireAdherant(f);
	afficheAdherant(ad, stdout);
	fclose(f);
}
*/
void testFonctionJeu(void)
{
	CodeErreur cErr;
	TableauJeu tabJeu;
	initTabJeu(&tabJeu);

	cErr = chargerTabJeu(&tabJeu, "donnee/jeux.don");
	if (cErr<0) return;

	afficheTabJeu(&tabJeu, stdout);
	fflush(stdout);

//ajout
	cErr = ajouterJeuInteractif(&tabJeu);
	if (cErr != ERR_NO_ERR) return;
	afficheTabJeu(&tabJeu, stdout);

//tri
	triTabJeu(&tabJeu, TRI_NOM);
	afficheTabJeu(&tabJeu, stdout);
	triTabJeu(&tabJeu, TRI_NB_EXEMPLAIRE_TOTAL);
	afficheTabJeu(&tabJeu, stdout);
	triTabJeu(&tabJeu, TRI_ID);
	afficheTabJeu(&tabJeu, stdout);

//suppresion
	cErr = retirerJeuInteractif(&tabJeu);
	if (cErr != ERR_NO_ERR) return;
	afficheTabJeu(&tabJeu, stdout);
	fflush(stdout);


//sauvegarde
	cErr = sauvegarderTabJeu(&tabJeu, "donnee/jeux2.don");
	if (cErr != ERR_NO_ERR) return;

	libererTabJeu(&tabJeu);
}
