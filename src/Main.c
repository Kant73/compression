#include <stdio.h>
#include <string.h>

#include "dictionnaire.h"
#include "decompression.h"

//DELAPORTE Adrien
//DUNAND Quentin
//NAVARRO Elsa
//POPEK Florian

int main(int argc, char* argv[])
{
	#ifdef DEBUG
		printf("<DEBUG MODE ENABLED>\n");
	#endif
	
	FILE* fileE;
	FILE* fileS;
	fileE = fopen(argv[2], "r");
	fileS = fopen(argv[3], "w");

	if (fileE == NULL)
	{
		printf("Impossible d'ouvrir le fichier...\n");
		return 1;
	}
	
	if (!strcmp(argv[1], "-c"))
		encode(fileE, fileS);
	else if (!strcmp(argv[1], "-d"))
		decode(fileE, fileS);
	
	fclose(fileE);
	fclose(fileS);
	
	printf("Terminé\n");
	
	return 0;
}