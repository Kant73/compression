#include <stdio.h>
#include <string.h>

#include "dictionnaire.h"

//DELAPORTE Adrien
//DUNAND Quentin
//NAVARRO Elsa
//POPEK Florian

int main(int argc, char* argv[])
{
	#ifdef DEBUG
		printf("<DEBUG MODE ENABLED>\n");
	#endif
	
	//TEST//
	///////////////////////////////////////////////////////
	type_dico* dictionnaire = calloc(1, sizeof(type_dico));
	initialiser_dico(dictionnaire);
	
	type_mot* mot = calloc(1, sizeof(type_mot));
	mot->lettre = 0;
	mot->suivant = calloc(1, sizeof(type_mot));
	mot->suivant->lettre = 0;


	uint8_t elem = 8;

	inserer_queue_mot(mot, elem);

	//printf("Mot déjà ajouté : %d\n", mot->suivant->lettre);
	//printf("Mot inserer : %d\n", mot->suivant->suivant->lettre);
	
	inserer_dico(mot, dictionnaire);
	printf("\n%d\n", chercher_code_dico(mot, dictionnaire));
	
	afficher_dico(dictionnaire);
	
	liberer_mot(mot);
	///////////////////////////////////////////////////////
	
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
