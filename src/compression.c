/*
	Projet CPS - Compression LZW
	Adrien DELAPORTE - Quentin DUNAND - Elsa NAVARRO - Florian POPEK
	compression.c
*/

#include <stdio.h>
#include <string.h>

#include "dictionnaire.h"
#include "compression.h"

/**
 * Permet d'encoder le fichier E dans le fichier S en utilisant le dictionnaire dico
 * @param E 	Le fichier qu'on veut encoder
 * @param S 	Le fichier qui contient le fichier encoder
 * @param dico 	Le dictionnaire
 */
void encode(FILE* E, FILE* S, type_dico* dico)
{
	type_mot mot, mot_concat;	//mot : Notre chaine d'octet; mot_concat: Contient la chaine d'octet concaténé avec l'octet courant
	mot_concat.suivant = NULL;

	int taille_code_max = 9;
	
	initialiser_dico(dico, COMP); //initialisation du Dico (paramètre COMP pour la compression)

	//A modifier eventuellement : on ouvrira les fichiers dans le main
	E = fopen("entree.txt", "r");
	S = fopen("sortie.txt", "w");
	
	if (E == NULL)
		printf("Impossible d'ouvir le fichier d'entrée...\n");

	init_mot(&mot, fgetc(E));	//On initialise le mot avec le premier octet de E
								//Correspond à w <- [1er octet de E]

	if (E != NULL)				//On teste si E n'est pas null ce qui signifierai 
	{							//que le fichier n'est pas ouvert
		while(!feof(E))			//Tant qu'on atteint pas la fin de fichier
		{
			affecter_mot(&mot_concat, &mot);	//mot_concat := mot

			uint8_t a = fgetc(E);				//On stocke dans a l'octet courant
			inserer_queue_mot(&mot_concat, a);	//On insère en queue de notre chaine d'octet l'octet courant

			#ifdef DEBUG
				printf("Caractère récupéré du fichier: %c\t%s\n", a, to_binaire(a));
			#endif
			
			int code = chercher_code_dico(&mot_concat, dico);	//code = -1 si mot_concat (w.a) non trouvé dans le dico
			if (code >= 0)										//Si mot_concat est dans le dico, code = code de mot_concat du dico
				inserer_queue_mot(&mot, a); //Equivalent à mot := mot_courant (w <- w.a)
			else 
			{
				int code_mot = chercher_code_dico(&mot, dico);
				paquet8_ecrire(code_mot, taille_code_max, S); 			//On ecrit dans le fichier le code du mot (w)
				inserer_dico(&mot_concat, dico, &taille_code_max, S);	//Et on insère le mot_concat (w.a) dans le dico
				
				if (mot.suivant != NULL)
					liberer_mot(mot.suivant);
				if (mot_concat.suivant != NULL)
				{
					liberer_mot(mot_concat.suivant);
					mot_concat.suivant = NULL; 
				}
				init_mot(&mot, a);
			}
		}
	}
	paquet8_ecrire(256, taille_code_max, S);	//Fin de fichier -> 256, on écris le fichier pour signaler la fin de fichier
	paquet8_ecrire(0, 7, S); 					//On compléter le fichier avec des 0
	
	//On libère tout à la fin de la compression du fichier
	if (mot.suivant != NULL)
		liberer_mot(mot.suivant);
	if (mot_concat.suivant != NULL)
		liberer_mot(mot_concat.suivant);
}
