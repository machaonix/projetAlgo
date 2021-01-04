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
	fprintf(flux, "%02d/%02d/%d", date.jour, date.mois, date.annee);
}
//---------------------------------------------------------------------------------------------------------------------------------
int dateCmp(Date date1, Date date2)
{
	int nbjour;
	short tabMois[12] = {0, 31, 59, 89, 120, 151, 181, 212, 243, 273, 304, 334};//Nombres de jours dans un mois cummulé

	//Calcule du nombre de jour ecoulé entre les deux Dates
	nbjour = abs((date1.annee-date2.annee)*tabMois[10]);
	nbjour += abs(tabMois[date1.mois-1] - tabMois[date2.mois-1]);
	nbjour += abs(date1.jour - date2.jour);

	/*
		Une année est bisecstille si elle est divisible par 4
		Une année n'est pas bisecstille si elle est divisible par 100
		Sauf si elle est divisible par 400
	*/
	for(int i=plusPetiteDate(&date1, &date2)->annee; i<=plusGrandeDate(&date1, &date2)->annee; ++i)
	{
		if(i%4 == 0 && plusPetiteDate(&date1, &date2)->mois >= 2)
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

	//ajustement du signe car on fait date1 - date2
	if(plusPetiteDate(&date1, &date2) == &date1)
		return nbjour*(-1);
	return nbjour;
}
//---------------------------------------------------------------------------------------------------------------------------------
Date *plusPetiteDate(Date *date1, Date *date2)
{
	//Une Date est plus petite qu'une autre si elle a une année plus petite
	if(date1->annee < date2->annee)
		return date1;
	if(date1->annee > date2->annee)
		return date2;

	//Une Date est plus petite qu'une autre si elle a la même année et que son mois est plus petit
	if(date1->mois < date2->mois)
		return date1;
	if(date1->mois > date2->mois)
		return date2;

	//Une Date est plus petite qu'une autre si elle a la même année, le même mois et que son jours est plus petit
	if(date1->jour < date2->jour)
		return date1;
	if(date1->jour > date2->jour)
		return date2;

	//Les 2 Dates sont égales
	return date1;
}
//---------------------------------------------------------------------------------------------------------------------------------
Date *plusGrandeDate(Date *date1, Date *date2)
{
	//Une Date est plus grande qu'une autre si elle a une année plus grande
	if(date1->annee < date2->annee)
		return date2;
	if(date1->annee < date2->annee)
		return date1;

	//Une Date est plus grande qu'une autre si elle a la même année et que son mois est plus grand
	if(date1->mois < date2->mois)
		return date2;
	if(date1->mois > date2->mois)
		return date1;

	//Une Date est plus grande qu'une autre si elle a la même année, le même mois et que son jours est plus grand
	if(date1->jour < date2->jour)
		return date2;
	if(date1->jour > date2->jour)
		return date1;

	//Les deux dates sont égales
	return date1;
}
