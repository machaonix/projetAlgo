#ifndef HG_TESTFONCTION_H
#define HG_TESTFONCTION_H

#ifdef TEST_DATE
#include "Date.h"
#endif //TEST_DATE

#ifdef TEST_ADHERANT
#include "Date.h"
#include "Adherant.h"
#endif //TEST_ADHERANT

#ifdef TEST_JEU
#include "TableauJeu.h"
#endif //TEST_JEU

void testFonction(void);

#endif //HG_TESTFONCTION_H
