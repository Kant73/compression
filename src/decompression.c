/*
	Projet CPS - Compression LZW
	Adrien DELAPORTE - Quentin DUNAND - Elsa NAVARRO - Florian POPEK
	decompression.h
 */

#include <stdio.h>
#include <string.h>

#include "../include/dictionnaire.h"
#include "../include/decompression.h"
	//lecture et écriture binaire
	//lecture en mode "buffer"


void decode(FILE* E, FILE* S){
	type_dico* dico;
	int i,j; //index dans D
	type_mot mot,mot2; // chaines d'octets
	uint8_t a;
	int taille_codes;
	initialiser_dico(dico, DECOMP);

	//E = fopen("entree.txt", "r");
	//S = fopen("sortie.txt", "w");

	if ((E != NULL)&&(S !=NULL))					//On teste si les fichiers sont bien ouverts 
	{

		i = paquet8_lire(E, &taille_codes); 		//récupère un premier code
		a = chercher_mot_dico(i, dico)->lettre; //a chaine cherchée, i code de la chaine ds le dico
		mot.lettre =a;
		ecrire_lettre(S, mot); 			//On écrit le mot sur le fichier de sortie

		while(!feof(E))					//Tant qu'on atteint pas la fin de fichier
			{
				j=paquet8_lire(E, &taille_codes); //on récupère l'entier suivant

				if(chercher_mot_dico(i, dico)!=NULL){
					mot2 = *chercher_mot_dico(i, dico);
					insereQueue(&mot2, a);
				}
				else{
					mot2 = *chercher_mot_dico(j, dico);
				}
				ecrire_lettre(S, mot2);
				a = mot2.lettre;
				insere_queue(&mot, a);
				inserer_dico(&mot, dico, &taille_codes, S);
				i=j;
				mot = *chercher_mot_dico(i, dico);
			}
	}
}