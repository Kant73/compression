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
	int i,j; //index dans D
	type_mot mot,mot2; // chaines d'octets
	uint8_t a;
	int taille_codes=9;
	dico = malloc(sizeof(type_dico));
	initialiser_dico(dico, DECOMP);

	//E = fopen("entree.txt", "r");
	//S = fopen("sortie.txt", "w");

	if ((E != NULL)&&(S !=NULL))					//On teste si les fichiers sont bien ouverts 
	{

		i = paquet8_lire(taille_codes, E); 		//récupère un premier code
		
		printf("code i : %d \n", i);
		
		a = chercher_mot_dico(i, dico)->lettre; //a chaine cherchée, i code de la chaine ds le dico
		init_mot(&mot, a);
		//mot.lettre =a;

		printf("mot : \n");
		afficher_mot(&mot);
		printf("fin afficher_mot\n");
		printf("&Mot : %p \n", mot);

		ecrire_lettre(S, &mot); 			//On écrit le mot sur le fichier de sortie

		while(!feof(E))					//Tant qu'on atteint pas la fin de fichier
			{

				printf("entree boucle\n");

				j=paquet8_lire(taille_codes, E); //on récupère l'entier suivant

				printf("code j : %d \n", j);

				if(chercher_mot_dico(i, dico)!=NULL){

					printf("Le mot est dans le dictionnaire \n");

					mot2 = *chercher_mot_dico(i, dico);

					printf("mot2 : \n");
					afficher_mot(&mot2);

					inserer_queue_mot(&mot2, a);

					printf("Insertion en queue terminée\n");
				}
				else{

					printf("Le mot n'est pas dans le dictionnaire \n");

					mot2 = *chercher_mot_dico(j, dico);

					printf("mot2 : \n");
					afficher_mot(&mot2);
				}
				ecrire_lettre(S, &mot2);

				printf("Ecriture du mot (mot2) : \n");
				afficher_mot(&mot2);

				a = mot2.lettre;

				printf("Insertion de la première lettre de mot2 dans mot: \n");

				inserer_queue_mot(&mot, a);

				printf("Insertion dans le dico du mot : \n");
				afficher_mot(&mot);

				printf("Insertion dans le dico \n");

				inserer_dico(&mot, dico, &taille_codes, S);

				printf("Insertion terminée \n");

				i=j;
				mot = *chercher_mot_dico(i, dico);
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