#include "TestFonction.h"

#ifdef TEST_DATE
void testFonction(void) //Date
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
#endif //TEST_DATE


#ifdef TEST_ADHERANT
void testFonction(void) //Adherant
{
	unsigned int tMax = 10;
	int nbElem = 0;
	Adherant* tAd = (Adherant*) malloc(sizeof(Adherant)*tMax);
	Adherant enPlus;
	Date uneDate = {29, 1, 2021};
	nbElem = chargerLesAdherants(tAd, &tMax, "../donnee/adherant.don");
	afficheTabAdherant(tAd, nbElem, stdout, TRUE);

	printf(" - - - - - - - -  - - - - - - - - - - - - - -\n");

	enPlus = nouvAdherant(404);
	nbElem = insererAdherant(tAd, nbElem, &tMax, &enPlus);

	afficheTabAdherant(tAd, nbElem, stdout, TRUE);
	sauvegarderAdherant(tAd, nbElem, "../donnee/adherant.don");
	//printf("Valide %d\n", checkInscriptionValide(&tAd[0], &uneDate));
	free(tAd);
}
#endif //TEST_ADHERANT

#ifdef TEST_JEU
 void testFonction(void) //Jeu
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
#endif //TEST_JEU

