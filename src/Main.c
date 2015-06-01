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
	
	if (argc != 5)
	{
		printf("\nPour compresser:\t./LZW -c <fichier_a_compresser> <fichier_compressé>\n");
		printf("Pour décompresser:\t./LZW -d <fichier_a_décompresser> <fichier_décompressé>\n\n");

		return;
	}

	FILE* fileE;
	FILE* fileS;
	fileE = fopen(argv[2], "r");
	fileS = fopen(argv[3], "w");

	if (fileE == NULL)
	{
		printf("\nImpossible d'ouvrir le fichier...\n");
		return 1;
	}
	
	if (!strcmp(argv[1], "-c"))
		encode(fileE, fileS);
	else if (!strcmp(argv[1], "-d"))
		decode(fileE, fileS);
	else
	{
		printf("\nPour compresser:\t./LZW -c <fichier_a_compresser> <fichier_compressé>\n");
		printf("Pour décompresser:\t./LZW -d <fichier_a_décompresser> <fichier_décompressé>\n\n");

		return;
	}

	fclose(fileE);
	fclose(fileS);
	
	printf("Terminé\n");
	
	return 0;
}