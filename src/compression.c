/*
	Projet CPS - Compression LZW
	Adrien DELAPORTE - Quentin DUNAND - Elsa NAVARRO - Florian POPEK
	compression.c
*/

#include <stdio.h>
#include <string.h>

#include "../include/dictionnaire.h"
#include "../include/compression.h"

/**
 * [encode description]
 * @param E 	Le fichier qu'on veut encoder
 * @param S 	Le fichier qui contient le fichier encoder
 * @param dic 	Le dictionnaire
 */
void encode(FILE* E, FILE* S, type_dico* dic)
{
	/*uint8_t a;				//Pour stocker un octet (l'octet courant)

	type_mot mot;			//Notre chaine d'octet
	type_mot mot_concat;	//Contient la chaine d'octet concaténé avec l'octet courant
	int code = -1;			//Contient le code d'une chaine d'octet
	int taille_code_max = 9;
	//initialisation du Dico
	initialiser_dico(dic);

	//A modifier : on ouvrira les fichier dans le main
	E = fopen("entree.txt", "r");
	S = fopen("sortie.txt", "w");

	init_mot(&mot, (uint8_t)fgetc(E));	//On initialise le mot avec le premier octet de E
										//Correspond à w <- [1er octet de E]
	
	mot_concat = mot;
	if (E != NULL)						//On teste si E n'est pas null ce qui signifierai 
	{									//que le fichier n'est pas ouvert
		while(!feof(E))					//Tant qu'on atteint pas la fin de fichier
		{
			a = (uint8_t)fgetc(E);				//On stocke dans a le caractère courant
			insere_queue_mot(mot_concat, a);	//On insère en queue de notre chaine d'octet l'octet courant
			if ( (code = chercher_mot(mot_concat)) >= 0)	//On stocke dans code le code du mot concatener
			{
				mot = mot_concat;
			}
			else 
			{
				//paquet8_ecrire(code, taille_code_max, S); 	//ecrire dans le fichier le code du mot
				inserer_dico(&mot_concat, dic, &taille_code_max, S);
				liberer_mot(&mot);
				init_mot(&mot, a);
			}
		}
		fprintf(S, "%d", code);	
	}
	liberer_mot(&mot);
	liberer_mot(&mot_concat);*/
}
