#include "Adherant.h"

Adherant lireAdherant(FILE* flux)
{
	//Déclaration de variables utiles
	Adherant adherantEnCourDeLecture;
	char civilite;

	//Lecture de l'identifient et de la civilitée de l'adhérant
	fscanf(flux, "%d%*c", &(adherantEnCourDeLecture.id));
	civilite = fgetc(flux);

	//determination de la civilitée a partir d'information lu
	switch(civilite)
	{
		case 'H':
			adherantEnCourDeLecture.civilite = HOMME;
			break;
		case 'F':
			adherantEnCourDeLecture.civilite = FEMME;
			break;
		default:
			adherantEnCourDeLecture.civilite = INCONU;
			break;
	}
	
	//lecture du nom et du prénom de l'adhérant
	fscanf(flux, "%s%s%*c", adherantEnCourDeLecture.nom, adherantEnCourDeLecture.prenom);

	//Lecture de la date d'inscription de l'adhérant
	adherantEnCourDeLecture.dateInscri = lireDate(flux);

	return adherantEnCourDeLecture;
}

void afficheAdherant(Adherant ad, FILE* flux)
{
	//affichage d'une entete si le flux est la sortie standard
	if(flux == stdout)
		printf("ID  CIVILITÉE\tNOM\tPRENOM\tDate\n");

	//affichage de l'identifient et de la civilitée
	switch(ad.civilite)
	{
		case HOMME:
			fprintf(flux, "%d\tH\t", ad.id);
			break;
		case FEMME:
			fprintf(flux, "%d\tF\t", ad.id);
			break;
		default:
			fprintf(flux, "%d\tI\t", ad.id);
			break;
	}

	//affichage du reste des attributs de l'adhérant (nopm, prénom, date d'inscription)
	printf("%s\t%s\t", ad.nom, ad.prenom);
	afficherDate(ad.dateInscri, flux);
	printf("\n");
}