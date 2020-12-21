#include "TestFonction.h"



void testFonctionJeu(void)
{
	// Jeu jeu;

	// jeu = nouvJeu(0);
	// afficheJeu(&jeu, stdout);

	//- - - - - - - - - -  - -
	//Test Date
	Date d1 = {31, 12, 2020};
	Date d2 = {1, 1, 2020};

	for(int i=1; i<=12; ++i)
		{
			d2.mois = i;
			printf("%d\n", dateCmp(d1, d2));
		}
	afficherDate(d1, stdout);
	//- - - - - - - - - -  - -
	
}