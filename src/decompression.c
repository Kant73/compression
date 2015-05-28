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

void decode(FILE* E, FILE* S, type_dico* dico){/*
	int i,j; //index dans D
	type_mot* mot,mot2; // chaines d'octets
	uint8_t a;
	initialiser_dico(dico);

	E = fopen("entree.txt", "r");
	S = fopen("sortie.txt", "w");

	if ((E != NULL)&&(F !=NULL))					//On teste si les fichiers sont bien ouverts 
	{
		i = recupereNextCodeFile(E); 		//récupère un premier code
		a = getChaine(i, dico).valeur; //a chaine cherchée, i code de la chaine ds le dico
		mot.lettre =a;
		ecrire_lettre(S, mot); 			//On écrit le mot sur le fichier de sortie

		while(!feof(E))					//Tant qu'on atteint pas la fin de fichier
			{
				j=recupereNextCodeFile(E);
				if(chercher_code_dico(mot, dico)==-1){
					mot2 = getChaine(i, dico);
					insereQueue(&mot2, a);
				}
				else{
					mot2 = getChaine(j, dico);
				}
				ecrire_lettre(S, mot2);
				a = mot2.lettre;
				insereQueue(&mot, a);
				inserer_dico(mot, dico);
				i=j;
				w= getChaine(i, dico);
			}
	}*/
}