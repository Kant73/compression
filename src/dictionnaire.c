#include "../include/dictionnaire.h"
#include <math.h>

void initialiser_dico(type_dico* dico, enum type_enum m)
{
	if (dico == NULL) //Dico vide
		return;
	
	mode = m;
	cpt = 258;

	int i;
	for (i = 0; i < 256; i++)
	{
		dico->branches[i] = malloc(sizeof(type_code));
		dico->branches[i]->code = i;
		dico->branches[i]->suivant = NULL;
	}

	dico->parent = malloc(sizeof(type_cellule));
	dico->parent->dico_contenant = NULL;

	if (mode == DECOMP)
	{
		tableau[0] = calloc(4096, sizeof(type_cellule));
	
		int i;
		for (i = 0; i < 256; i++)
		{
			type_cellule c;
			c.indice = i;
			c.dico_contenant = dico;

			tableau[0][i] = c;
		}
	}

}

void inserer_dico(type_mot* mot, type_dico* dico, int* taille_code, FILE* S)
{
	if (dico == NULL || mot == NULL || mot->suivant == NULL) //Dico ou mot vide
		return;
	
	type_dico* temp_dico = dico;
	type_mot* temp_mot = mot;
	
	while (temp_mot->suivant != NULL)
	{
		if (temp_dico->branches[temp_mot->lettre]->suivant == NULL)
		{
			temp_dico->branches[temp_mot->lettre]->suivant = calloc(1, sizeof(type_dico));
			temp_dico->branches[temp_mot->lettre]->suivant->parent->dico_contenant = temp_dico;
			temp_dico->branches[temp_mot->lettre]->suivant->parent->indice = temp_mot->lettre;
		}

		temp_dico = temp_dico->branches[temp_mot->lettre]->suivant;
		temp_mot = temp_mot->suivant;
	}

	temp_dico->branches[temp_mot->lettre] = malloc(sizeof(type_code));
	temp_dico->branches[temp_mot->lettre]->code = cpt;
	temp_dico->branches[temp_mot->lettre]->suivant = NULL;

	if (mode == DECOMP)
		ajouter_element(temp_mot->lettre, temp_dico);

	cpt++;
	
	if (cpt == pow(*taille_code, 2) - 1)
	{
		(*taille_code) ++;
		paquet8_ecrire(256, 9, S);
	}

}

void ajouter_element(uint8_t i, type_dico* d)
{
	type_cellule c;
	c.indice = i;
	c.dico_contenant = d;

	tableau[cpt/4096][cpt - cpt/4096] = c;
}

type_mot* chercher_mot_dico(int code, type_dico* dico)
{
	if (dico == NULL)
		return;

	return mot_associe(tableau[code/4096][code - code/4096].dico_contenant, tableau[code/4096][code - code/4096].indice);
}

int chercher_code_dico(type_mot* mot, type_dico* dico)
{
	if (dico == NULL || mot == NULL) //Dico ou mot vide
		return -1;
		
	type_mot* temp_mot = mot;
	type_dico* temp_dico = dico;
	while (1)
	{
		if (temp_dico != NULL && temp_dico->branches[temp_mot->lettre] != NULL)
		{
			if (temp_mot->suivant == NULL)
				break;
			
			temp_dico = temp_dico->branches[temp_mot->lettre]->suivant;
			temp_mot = temp_mot->suivant;
		}
		else
			return -1;
	}
	
	return temp_dico->branches[temp_mot->lettre]->code;
}

void afficher_dico(type_dico* dico)
{
	if (dico != NULL)
	{
		int i;
		for (i = 0; i < 256; i++)
		{
			if (dico->branches[i] != NULL)
				printf("%d\n", dico->branches[i]->code);
		}
		
		printf("\n");
		for (i = 0; i < 256; i++)
		{
			if (dico->branches[i] != NULL)
				afficher_dico(dico->branches[i]->suivant);
		}
	}
}

void liberer_mot(type_mot* mot)
{
	type_mot* temp_mot = mot;
	while (temp_mot != NULL)
	{
		mot = temp_mot->suivant;
		free(temp_mot);
		temp_mot = mot;
	}
}

void liberer_dico(type_dico* dico)
{
	if (dico == NULL)
		return;
		
	int i;
	for (i = 0; i < 256; i++)
	{
		if (dico->branches[i] != NULL)
		{
			liberer_dico(dico->branches[i]->suivant);
			free(dico->branches[i]);
		}
	}
	free(dico);
}

void paquet8_ecrire(int code, int taille, FILE* S)
{
	if (taille <= 0) //Taille invalide
		return;
	
	//Initialisation des statics
	static uint8_t buffer_s = 0;
	static int taille_s = 0;
	
	//////////////
	uint8_t temp; //Valeur à retourner

	if (taille_s > 0) //Si le buffer n'est pas vide
	{
		temp = (code >> (taille - 8 + taille_s)) + buffer_s;
		
		//Ecrire dans le fichier le mot temp
		fprintf(S, "%c", temp);	
		taille = taille - 8 + taille_s;
	}
	
	taille_s = 0;
	buffer_s = 0;

	while (taille >= 8)
	{
		temp = code >> (taille - 8);
		
		//Ecrire dans le fichier le mot temp
		fprintf(S, "%c", temp);
		
		taille = taille - 8;
	}
	
	if (taille > 0)	
	{
		taille_s = taille;
		buffer_s = code << (8 - taille_s);
	}

	#ifdef DEBUG
		printf("paquet8_ecrire:\n");
		printf("\tTaille buffer: %d\n", taille_s);
		printf("\tBuffer: %s\n", to_binaire(buffer_s >> (8 - taille_s)));
	#endif
}


char * to_binaire(unsigned long int arg)
{
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (arg & 1); arg >>= 1; } while (arg);
    return p;
}

int paquet8_lire(int taille, FILE* S)
{
	if (taille <= 0)
		return -1;
		
	static uint8_t buffer_s = 0;
	static int taille_s = 0;
	
	//////////////
	int result = 0;

	if (taille_s > 0)
	{
		int temp = buffer_s;
		temp = temp << (taille - taille_s);
		result += temp;
		
		taille -= taille_s;
	}
	
	taille_s = 0;
	buffer_s = 0;

	while (taille >= 8)
	{
		int temp2 = fgetc(S) << (taille - 8);
		result += temp2;
		
		taille = taille - 8;
	}
	
	if (taille > 0) //Rajouter reste
	{	
		taille_s = 8-taille;
		
		uint8_t temp = fgetc(S);
		buffer_s = temp;
		
		temp = temp >> taille_s;
		result += temp;
		
		uint8_t mask = -1;
		mask = mask >> taille;
		buffer_s &= mask;
	}
	
	return result;
}


void affecter_mot(type_mot* mot1, type_mot* mot2)
{
	if (mot1 == NULL || mot2 == NULL)
		return;

	type_mot* temp = mot1->suivant;
	while (temp != NULL)
	{
		type_mot* temp2 = temp->suivant;
		free(temp);
		temp = temp2;
	}


	mot1->lettre = mot2->lettre;
	mot1->suivant = NULL;

	temp = mot1;
	mot2 = mot2->suivant;
	while (mot2 != NULL)
	{
		temp->suivant = malloc(sizeof(type_mot));
		temp = temp->suivant;

		temp->lettre = mot2->lettre;
		mot2 = mot2->suivant;
	}	
}

void afficher_mot(type_mot* mot)
{
	while (mot != NULL)
	{
		printf("%c", mot->lettre);
		mot = mot->suivant;
	}
	printf("\n");
}


type_mot* mot_associe(type_dico* dico, uint8_t indice)
{
	if (dico == NULL)
		return NULL;
		
	type_mot* liste = malloc(sizeof(type_mot));
	type_mot* temp = liste;
	
	temp->lettre = dico->branches[indice]->code;
	while (dico->parent->dico_contenant != NULL)
	{
		temp->suivant = malloc(sizeof(type_mot));
		temp = temp->suivant;
		temp->suivant = NULL;
		
		dico = dico->parent->dico_contenant;
		
		temp->lettre = dico->branches[indice]->code;
	}
	
	return liste;
}

void inserer_queue_mot(type_mot* mot, uint8_t elem)
{
	if (mot != NULL)
	{
		type_mot* temp_mot = mot;
		while(temp_mot->suivant != NULL)
			temp_mot = temp_mot->suivant;
			
		temp_mot->suivant = malloc(sizeof(type_mot));
		temp_mot->suivant->lettre = elem;
		temp_mot->suivant->suivant = NULL;
	}
}


void init_mot(type_mot* mot, uint8_t val_init)
{
	if (mot == NULL)
		return;
		
	mot->lettre = val_init;
	mot->suivant = NULL;
}
