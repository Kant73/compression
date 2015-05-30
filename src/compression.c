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
	type_mot mot, mot_concat;	//Notre chaine d'octet , //Contient la chaine d'octet concaténé avec l'octet courant
	mot_concat.suivant = NULL;

	int taille_code_max = 9;
	
	initialiser_dico(dico, COMP); //initialisation du Dico

	//A modifier : on ouvrira les fichier dans le main
	E = fopen("entree.txt", "r");
	S = fopen("sortie.txt", "w");
	
	if (E == NULL)
		printf("Impossible d'ouvir le fichier...\n");

	init_mot(&mot, fgetc(E));	//On initialise le mot avec le premier octet de E
										//Correspond à w <- [1er octet de E]
	printf("lol\n");

	if (E != NULL)						//On teste si E n'est pas null ce qui signifierai 
	{									//que le fichier n'est pas ouvert
		while(!feof(E))					//Tant qu'on atteint pas la fin de fichier
		{
			affecter_mot(&mot_concat, &mot);

			uint8_t a = fgetc(E);				//On stocke dans a le caractère courant
			inserer_queue_mot(&mot_concat, a);	//On insère en queue de notre chaine d'octet l'octet courant

			#ifdef DEBUG
				printf("Caractère récupéré du fichier: %c\t%s\n", a, to_binaire(a));
			#endif
			
			int code = chercher_code_dico(&mot_concat, dico);
			if (code >= 0)
				inserer_queue_mot(&mot, a); //On stocke dans code le code du mot concatené
			else 
			{
				int code_mot = chercher_code_dico(&mot, dico);
				paquet8_ecrire(code_mot, taille_code_max, S); 	//ecrire dans le fichier le code du mot
				inserer_dico(&mot_concat, dico, &taille_code_max, S);
				
				if (mot.suivant != NULL)
					liberer_mot(mot.suivant);
				if (mot_concat.suivant != NULL)
					liberer_mot(mot_concat.suivant); 
				mot_concat.suivant = NULL;
				init_mot(&mot, a);
			}
		}
	}
	paquet8_ecrire(256, taille_code_max, S); //Fin de fichier -> 256
	paquet8_ecrire(0, 7, S); //Compléter avec des 0
	
	if (mot.suivant != NULL)
		liberer_mot(mot.suivant);
	if (mot_concat.suivant != NULL)
		liberer_mot(mot_concat.suivant);
}
