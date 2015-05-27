/*
	Projet CPS - Compression LZW
	Adrien DELAPORTE - Quentin DUNAND - Elsa NAVARRO - Florian POPEK
	compression.c
*/

#include <stdio.h>
#include <string.h>

#include "compression.h"
#include "dictionnaire.h"

/**
 * [encode description]
 * @param
 * @param
 * @param
 */
void encode(file* E, file* S, dico* dic)
{
	uint8_t a;		//Pour stocker un octet (l'octet courant)

	type_mot mot;
	type_mot mot_concat;
	int code = -1;
	//initialisation du Dico
	initialiserDico(dic);

	//A modifier : on ouvrira les fichier dans le main
	E = fopen("entree.txt", "r");
	S = fopen("sortie.txt", "w");

	initMot(mot, (uint8_t)fgetc(E));
	//insereQueue(mot, fgetc(E));
	mot_concat = mot;
	if (E != NULL) 
	{
		while(!feof(E))
		{
			a = fgetc(E);
			insereQueue(mot_concat, a);
			if ( (code = chercherDico(mot_concat)) >= 0)
			{
				mot = mot_concat;
			}
			else 
			{
				fprintf(S, "%d", code);
				insererDico(mot_concat, dic);
				libererMot(mot);
				initMot(mot, a);
			}
		}
		fprintf(S, "%d", code);	
	}
	libererMot(mot);
	libererMot(mot_concat);


}