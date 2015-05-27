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
 * @param E 	Le fichier qu'on veut encoder
 * @param S 	Le fichier qui contient le fichier encoder
 * @param dic 	Le dictionnaire
 */
void encode(file* E, file* S, type_dico* dic)
{
	uint8_t a;				//Pour stocker un octet (l'octet courant)

	type_mot mot;			//Notre chaine d'octet
	type_mot mot_concat;	//Contient la chaine d'octet concaténé avec l'octet courant
	int code = -1;			//Contient le code d'une chaine d'octet
	
	//initialisation du Dico
	initialiser_dico(dic);

	//A modifier : on ouvrira les fichier dans le main
	E = fopen("entree.txt", "r");
	S = fopen("sortie.txt", "w");

	initMot(mot, (uint8_t)fgetc(E));	//On initialise le mot avec le premier octet de E
										//Correspond à w <- [1er octet de E]

	
	mot_concat = mot;
	if (E != NULL)						//On teste si E n'est pas null ce qui signifierai 
	{									//que le fichier n'est pas ouvert
		while(!feof(E))					//Tant qu'on atteint pas la fin de fichier
		{
			a = fgetc(E);				//On stock dans a le caractère courant
			insereQueue(mot_concat, a);	//On insère en queue de notre chaine d'octet l'octet courant
			if ( (code = chercher_mot(mot_concat)) >= 0)	//On stock dans code le code du mot concatener
			{
				mot = mot_concat;
			}
			else 
			{
				fprintf(S, "%d", code);
				inserer_dico(mot_concat, dic);
				liberer_mot(mot);
				init_mot(mot, a);
			}
		}
		fprintf(S, "%d", code);	
	}
	liberer_mot(mot);
	liberer_mot(mot_concat);


}