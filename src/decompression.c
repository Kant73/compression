/*
	Projet CPS - Compression LZW
	Adrien DELAPORTE - Quentin DUNAND - Elsa NAVARRO - Florian POPEK
	decompression.h
 */

#include <stdio.h>
#include <string.h>

#include "dictionnaire.h"
#include "decompression.h"

void decode(FILE* E, FILE* S)
{
	type_dico* dico;
	int i,j; //index dans D (code du mot)
	type_mot mot,mot2; // chaines d'octets
	uint8_t a;
	type_mot* temp;
	int taille_code_max = 9;

	//On initialise notre dictionnaire de décompression
	dico = calloc(1, sizeof(type_dico));
	initialiser_dico(dico, DECOMP);

	i = paquet8_lire(taille_code_max, E); //on récupère le premier code du fichier d'entrée

	temp = chercher_mot_dico(i, dico);
	a = temp->lettre; 
	free(temp);

	mot.lettre = a;
	mot.suivant = NULL;

	mot2.suivant = NULL;

	ecrire_lettre(S, &mot); 			

	while (!feof(E)) //Tant qu'on atteint pas la fin de fichier
	{
		j = paquet8_lire(taille_code_max, E);
		if (j == 256)
			break; //Fin de fichier
		else if (j == 257)
			taille_code_max ++;
		else if (j == 258) //Réinitialisation
		{
			vider_dico(dico, &taille_code_max);
			
			i = paquet8_lire(taille_code_max, E); //on récupère le premier code du fichier d'entrée

			if (i == 256)
				break;

			temp = chercher_mot_dico(i, dico);
			a = temp->lettre; 
			free(temp);

			mot.lettre = a;
			mot.suivant = NULL;

			mot2.suivant = NULL;

			ecrire_lettre(S, &mot); 
		}
		else
		{
			temp = chercher_mot_dico(j, dico);
			if (temp == NULL) //Si le mot n'est pas présent dans le dico
			{	
				temp = chercher_mot_dico(i, dico);
				affecter_mot(&mot2, temp);	
				free(temp);

				inserer_queue_mot(&mot2, a);
			}
			else
			{
				affecter_mot(&mot2, temp);
				free(temp);
			}

			ecrire_lettre(S, &mot2);
			a = mot2.lettre;

			inserer_queue_mot(&mot, a);
			inserer_dico(&mot, dico, &taille_code_max, S);

			i=j;
			temp = chercher_mot_dico(i, dico);
			affecter_mot(&mot, temp);
			free(temp);
		}
	}

	if (mot.suivant != NULL)
		liberer_mot(mot.suivant);
	if (mot2.suivant != NULL)
		liberer_mot(mot2.suivant);

	liberer_dico(dico);
}

void ecrire_lettre(FILE* S, type_mot* mot){
	while (mot != NULL)
	{
		fprintf(S, "%c", mot->lettre);
		mot = mot->suivant;
	}
}