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
	TableauJeu* tabJeu = nouvTabJeu();
	if (tabJeu == NULL)
		return;

	cErr = chargerTabJeu(tabJeu, "donnee/jeux.don");
	if (cErr<0) return;

	afficheTabJeu(tabJeu, stdout);
	cErr = ajouterJeu(tabJeu, nouvJeu(genIdJeu(tabJeu)));
	if (cErr<0) return;
	
	afficheTabJeu(tabJeu, stdout);

	triTabJeu(tabJeu, TRI_NOM);

	
	afficheTabJeu(tabJeu, stdout);
	triTabJeu(tabJeu, TRI_ID);
	
	afficheTabJeu(tabJeu, stdout);
	triTabJeu(tabJeu, TRI_NB_EXEMPLAIRE_TOTAL);
	
	afficheTabJeu(tabJeu, stdout);

	cErr = retirerJeu(tabJeu, 1);
	if (cErr<0) return;
	afficheTabJeu(tabJeu, stdout);
	libererTabJeu(tabJeu);
}
