#include <stdio.h>
#include <string.h>

//DELAPORTE Adrien
//DUNAND Quentin
//NAVARRO Elsa
//POPEK Florian

int main(int argc, char* argv[])
{
	#ifdef DEBUG
		printf("<DEBUG MODE ENABLED>\n");
	#endif
	
	FILE* file;
	//file = fopen(/*nom du fichier*/, "r");
	
	
	if (file == NULL)
	{
		printf("Impossible d'ouvrir le fichier...\n");
		return 1;
	}
	
	while (!feof(file)) //Lire les mots
	{
		
	}
	
	fclose(file);
	
	//Libérer la mémoire
	
	return 0;
}
