/*
	Projet CPS - Compression LZW
	Adrien DELAPORTE - Quentin DUNAND - Elsa NAVARRO - Florian POPEK
	decompression.h
 */

#include <stdio.h>
#include <string.h>

#include "dictionnaire.h"
#include "decompression.h"
	//lecture et écriture binaire
	//lecture en mode "buffer"


void decode(FILE* E, FILE* S){

	type_dico* dico;
	int i,j; //index dans D (code du mot)
	type_mot mot,mot2; // chaines d'octets
	uint8_t a;
	int taille_codes=9;

	//On initialise notre dictionnaire de décompression
	dico = calloc(1, sizeof(type_dico));
	initialiser_dico(dico, DECOMP);

	//E = fopen("entree.txt", "r");
	//S = fopen("sortie.txt", "w");

	if ((E != NULL)&&(S !=NULL))	//On teste si les fichiers sont bien ouverts 
	{
		i = paquet8_lire(taille_codes, E); //on récupère le premier code du fichier d'entrée
		a = chercher_mot_dico(i, dico)->lettre; 

		init_mot(&mot, a);
		init_mot(&mot2, a); 

		ecrire_lettre(S, &mot); 			

		while (!feof(E)) //Tant qu'on atteint pas la fin de fichier
		{
			j = paquet8_lire(taille_codes, E);
			if (j == 256)
				break; //Fin de fichier
			else if (j == 257)
				taille_codes ++;
			else if (j == 258)
				vider_dico(dico, &taille_codes);
			else
			{

				if (chercher_mot_dico(j, dico) == NULL) //Si le mot n'est pas présent dans le dico
				{	
					affecter_mot(&mot2, chercher_mot_dico(i, dico));	
					inserer_queue_mot(&mot2, a);
				}
				else
					affecter_mot(&mot2, chercher_mot_dico(j, dico));
				
				ecrire_lettre(S, &mot2);
				a = mot2.lettre;

				inserer_queue_mot(&mot, a);
				inserer_dico(&mot, dico, &taille_codes, S);

				i=j;
				affecter_mot(&mot, chercher_mot_dico(i, dico));
			}
		}
	}
}

void ecrire_lettre(FILE* S, type_mot* mot){
	while (mot != NULL)
	{
		fprintf(S, "%c", mot->lettre);
		mot = mot->suivant;
	}
}