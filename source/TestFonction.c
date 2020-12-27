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
}*/

void testFonctionJeu(void)
{
	CodeErreur cErr;
	TableauJeu tabJeu;
	initTabJeu(&tabJeu);

	cErr = chargerTabJeu(&tabJeu, "donnee/jeux.don");
	if (cErr<0) return;

	afficheTabJeu(&tabJeu, stdout);
	fflush(stdout);

	cErr = ajouterJeuInteractif(&tabJeu);
	if (cErr<0) return;

	afficheTabJeu(&tabJeu, stdout);
	fflush(stdout);
	cErr = sauvegarderTabJeu(&tabJeu, "donnee/jeux2.don");
	if (cErr<0) return;

	libererTabJeu(&tabJeu);
}
