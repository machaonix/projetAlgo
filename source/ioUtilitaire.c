#include "ioUtilitaire.h"

Bool IO_Choix_O_N(char message[])
{
	char choix;
	printf("%s (O/N) ? : ", message);
	fflush(stdout);
	scanf("%c%*c", &choix);
	while (choix != 'O' && choix != 'N')
	{
		printf("Veuillez par O ou par N : ");
		fflush(stdout);
		scanf("%c%*c", &choix);
	}
	if (choix == 'O')
		return TRUE;
	return FALSE;
}
