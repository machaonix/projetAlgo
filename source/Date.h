#ifndef __DATE_H__
#define __DATE_H__

#include <stdio.h>
#include <stdlib.h>
#include "CodeErreur.h"

typedef struct {
  int jour;
  int mois;
  int annee;
} Date;

Date lireDate(FILE* flux);
void afficherDate(Date date, FILE* flux);

//          dateCmp
//retourne ecart en jour    negative si date1<date2
//                          positive si date1>date2
//                          nulle    si date1==date2     
int dateCmp(Date date1, Date date2);

Date *plusPetiteDate(Date *date1, Date *date2);
Date *plusGrandeDate(Date *date1, Date *date2);

#endif //__DATE_H__
