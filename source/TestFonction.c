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
	Jeu* tJeu[10];
	int nbElements;

	nbElements = chargerTabJeu(tJeu, "donnee/jeux.don", 10);
	if (nbElements<0) return;

	afficheTabJeu(tJeu, nbElements, stdout);
	nbElements = ajouterJeu(tJeu, nbElements, nouvJeu(genIdJeu(tJeu, nbElements)), 10);
	afficheTabJeu(tJeu, nbElements, stdout);
	triJeu(tJeu, nbElements, TRI_NOM);
	afficheTabJeu(tJeu, nbElements, stdout);
	triJeu(tJeu, nbElements, TRI_ID);
	afficheTabJeu(tJeu, nbElements, stdout);
	triJeu(tJeu, nbElements, TRI_NB_EXEMPLAIRE_TOTAL);
	afficheTabJeu(tJeu, nbElements, stdout);


	nbElements = retirerJeu(tJeu, nbElements, 1);
	afficheTabJeu(tJeu, nbElements, stdout);
	libererTabJeu(tJeu, &nbElements);
}
