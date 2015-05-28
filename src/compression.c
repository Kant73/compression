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
 * @param dico 	Le dictionnaire
 */
void encode(FILE* E, FILE* S, type_dico* dico)
{
	/*uint8_t a;				//Pour stocker un octet (l'octet courant)

	type_mot mot;			//Notre chaine d'octet
	type_mot mot_concat;	//Contient la chaine d'octet concaténé avec l'octet courant
	int code = -1;			//Contient le code d'une chaine d'octet
	int code_mot = -1;
	int taille_code_max = 9;
	//initialisation du Dico
	initialiser_dico(dico);

	//A modifier : on ouvrira les fichier dans le main
	E = fopen("entree.txt", "r");
	S = fopen("sortie.txt", "w");

	init_mot(&mot, fgetc(E));	//On initialise le mot avec le premier octet de E
										//Correspond à w <- [1er octet de E]
	
	
	if (E != NULL)						//On teste si E n'est pas null ce qui signifierai 
	{									//que le fichier n'est pas ouvert
		while(!feof(E))					//Tant qu'on atteint pas la fin de fichier
		{
			mot_concat = mot;
			a = fgetc(E);				//On stocke dans a le caractère courant
			inserer_queue_mot(&mot_concat, a);	//On insère en queue de notre chaine d'octet l'octet courant
			/*type_mot* tmp = &mot_concat;
			while(tmp != NULL)
			{
				printf("%d\n", tmp->lettre);
				tmp = tmp->suivant;
			}
			*/
			//printf("mot_concat.lettre %d\n", mot_concat.lettre);
			//printf("mot_concat.suivant->lettre %d\n", mot_concat.suivant->lettre);
			code = chercher_code_dico(&mot_concat, dico);
			//printf("Code mot_concat %d\n", code);
			if (code >= 0)	//On stocke dans code le code du mot concatener
			{
				mot = mot_concat;
			}
			else 
			{
				code_mot = chercher_code_dico(&mot, dico);
				printf("Code_mot %d\n", code_mot);
				paquet8_ecrire(code_mot, taille_code_max, S); 	//ecrire dans le fichier le code du mot
				inserer_dico(&mot_concat, dico, &taille_code_max, S);
				liberer_mot(mot.suivant);
				liberer_mot(mot_concat.suivant);
				init_mot(&mot, a);
				printf("mot.lettre %d\n", mot.lettre);
				//printf("Mot.lettre: %d\n", mot.lettre);
				//printf("Pointeur sur mot suivant : %d\n", mot.suivant);

			}
		}
	}
<<<<<<< HEAD
	liberer_mot(&mot);
	liberer_mot(&mot_concat);*/
}
=======
	//liberer_mot(mot.suivant);
	//liberer_mot(mot_concat.suivant);
	//liberer_dico(dico);
	//afficher_dico(dico);
}
>>>>>>> 1cd653694daf23ab782aac4e42a131281d44a7b9
