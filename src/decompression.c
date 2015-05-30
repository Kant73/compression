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
	dico = malloc(sizeof(type_dico));
	initialiser_dico(dico, DECOMP);

	//E = fopen("entree.txt", "r");
	//S = fopen("sortie.txt", "w");

	if ((E != NULL)&&(S !=NULL))	//On teste si les fichiers sont bien ouverts 
	{
			//on récupère le premier code du fichier d'entrée
		i = paquet8_lire(taille_codes, E); 		
		
			printf("code i : %d \n", i);
		
			//a récupère la chaine correspondant au code i dans le dico 
			//-> une simple lettre à cet instant
		a = chercher_mot_dico(i, dico)->lettre; 

			//mot récupère cette lettre
		init_mot(&mot, a);

			//On initialise mot2 pour éviter des problèmes de free et autre plus tard
			//la valeur prise par mot2 n'a pas d'impact par la suite
		init_mot(&mot2, a); 

			printf("mot : ");
			afficher_mot(&mot);
			printf("Ecriture du mot\n");

			//On écrit le mot sur le fichier de sortie
		ecrire_lettre(S, &mot); 			

		while(!feof(E))					//Tant qu'on atteint pas la fin de fichier
			{
				//invariant : a est la première lettre de mot2
				printf("!---------------entree boucle--------------!\n");
					printf("valeur de a : %d \n", a);
					printf("mot courant : ");
					afficher_mot(&mot);


					//on récupère le code suivant dans le fichier d'entrée
				j=paquet8_lire(taille_codes, E); 

					printf("code j : %d \n", j);
					printf("code i : %d \n", i);


					//Si le mot n'est pas présent dans le dico
				if(chercher_mot_dico(j, dico)==NULL){	

						printf("Le mot correspondant au code %d (j) n'est pas dans le dictionnaire \n", j);

						//mot2 récupère le mot correspondant au code précédent (i)
					affecter_mot(&mot2, chercher_mot_dico(i, dico));	

						//et il y concatène la lettre lue précedemment
					inserer_queue_mot(&mot2, a);

						printf("mot2 : ");
						afficher_mot(&mot2);
				}
				else{	//Sinon le mot est dans le dico

						printf("Le mot correspondant au code %d (j) est dans le dictionnaire \n", j);

						//mot2 récupère ce mot
					affecter_mot(&mot2, chercher_mot_dico(j, dico));
					//mot2 = *chercher_mot_dico(j, dico);

						printf("mot2 : \n");
						afficher_mot(&mot2);
				}
				ecrire_lettre(S, &mot2);

					printf("Ecriture de mot2 dans notre fichier décompressé \n");

				a = mot2.lettre;

					printf("valeur de a : %d \n", a);
					printf("Insertion de cette lettre dans mot: \n");

				inserer_queue_mot(&mot, a);

					printf("Insertion dans le dico du mot obtenu : ");
					afficher_mot(&mot);

				inserer_dico(&mot, dico, &taille_codes, S);

					printf("Insertion terminée, on charge le mot suivant de code %d (j) dans mot\n", j);

				i=j;
				affecter_mot(&mot, chercher_mot_dico(i, dico));
				//mot = *chercher_mot_dico(i, dico);
				
					printf("Mot devient : ");
					afficher_mot(&mot);
					printf("!-----------fin de boucle------------!\n");
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