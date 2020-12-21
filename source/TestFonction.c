#include "TestFonction.h"



void testFonctionJeu(void)
{
	Jeu* tJeu[10];
	int nbElements;

	nbElements = chargerTabJeu(tJeu, "donnee/jeux.don", 10);
	if (nbElements<0) return;

	afficheTabJeu(tJeu, nbElements, stdout);
	nbElements = ajouterJeu(tJeu, nbElements, nouvJeu(genIdJeu(tJeu, nbElements)), 10);
	afficheTabJeu(tJeu, nbElements, stdout);
	nbElements = retirerJeu(tJeu, nbElements, 1);
	afficheTabJeu(tJeu, nbElements, stdout);
	libererTabJeu(tJeu, &nbElements);
}
