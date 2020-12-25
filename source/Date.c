#include "Date.h"


Date lireDate(FILE* flux)
{
	Date d;
	fscanf(flux, "%d/%d/%d%*c", &(d.jour), &(d.mois), &(d.annee));
	return d;
}
//---------------------------------------------------------------------------------------------------------------------------------
void afficherDate(Date date, FILE* flux)
{
	if(flux == stdout)
		printf("Jour/mois/année\n");
	fprintf(flux, "%d/%d/%d\n", date.jour, date.mois, date.annee);
}
//---------------------------------------------------------------------------------------------------------------------------------
int dateCmp(Date date1, Date date2)
{
	int nbjour;
	short tabMois[12] = {0, 31, 59, 89, 120, 150, 181, 212, 242, 273, 303, 334};//Nombres de jours dans un mois cummulé
	
	nbjour = abs((date1.annee-date2.annee)*tabMois[11]);
	nbjour += abs(tabMois[date1.mois-1] - tabMois[date2.mois-1]);
	nbjour += abs(date1.jour - date2.jour);
	for(int i=plusPetiteDate(&date1, &date2)->annee; i<=plusGrandeDate(&date1, &date2)->annee; ++i)
	{
		if(i%4 == 0 && plusPetiteDate(&date1, &date2)->mois > 2)
		{
			++nbjour;
			if(i%100 == 0)
			{
				--nbjour;
				if(i%400 == 0)
				{
					++nbjour;
				}
			}
		}
	}
	if(plusPetiteDate(&date1, &date2) == &date1)
		return nbjour*(-1);
	return nbjour;
}
//---------------------------------------------------------------------------------------------------------------------------------
Date *plusPetiteDate(Date *date1, Date *date2)
{
	if(date1->annee < date2->annee)
		return date1;
	if(date1->annee < date2->annee)
		return date2;

	if(date1->mois < date2->mois)
		return date1;
	if(date1->mois > date2->mois)
		return date2;

	if(date1->jour < date2->jour)
		return date1;
	if(date1->jour > date2->jour)
		return date2;

	return date1;
}
//---------------------------------------------------------------------------------------------------------------------------------
Date *plusGrandeDate(Date *date1, Date *date2)
{
	if(date1->annee < date2->annee)
		return date2;
	if(date1->annee < date2->annee)
		return date1;

	if(date1->mois < date2->mois)
		return date2;
	if(date1->mois > date2->mois)
		return date1;

	if(date1->jour < date2->jour)
		return date2;
	if(date1->jour > date2->jour)
		return date1;
	return date1;
}
