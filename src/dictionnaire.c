#include <math.h>

#include "../include/dictionnaire.h"

void initialiser_dico(type_dico* dico)
{
	if (dico == NULL) //Dico vide
		return;
		
	int i;
	for (i = 0; i < 256; i++)
	{
		dico->branches[i] = malloc(sizeof(type_code));
		dico->branches[i]->code = i;
		dico->branches[i]->suivant = NULL;
		dico->branches[i]->parent = NULL;
	}
}

void inserer_dico(type_mot* mot, type_dico* dico, int* taille_code, FILE* S)
{
	static int cpt = 258;
	
	if (dico == NULL || mot == NULL || mot->suivant == NULL) //Dico ou mot vide
		return;
	
	type_dico* temp_dico = dico;
	type_mot* temp_mot = mot;
	
	while (temp_mot->suivant != NULL)
	{
		if (temp_dico->branches[temp_mot->lettre]->suivant == NULL)
			temp_dico->branches[temp_mot->lettre]->suivant = calloc(1, sizeof(type_dico));
		
		temp_dico = temp_dico->branches[temp_mot->lettre]->suivant;
		temp_mot = temp_mot->suivant;
	}

	temp_dico->branches[temp_mot->lettre] = malloc(sizeof(type_code));
	temp_dico->branches[temp_mot->lettre]->code = cpt;
	temp_dico->branches[temp_mot->lettre]->suivant = NULL;

	cpt++;
	
	if (cpt == pow(*taille_code, 2) - 1)
	{
		(*taille_code) ++;
		paquet8_ecrire(256, 9, S);
	}

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

int nbr_bit(int code)
{
	if (code < 256)
		return 8;
	return log((double)code) / log(2.0);
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

type_mot* mot_associe(type_code* arg)
{
	if (arg == NULL)
		return NULL;
		
	type_mot* liste = malloc(sizeof(type_mot));
	type_mot* temp = liste;
	
	temp->lettre = arg->code;
	while (arg->parent != NULL)
	{
		temp->suivant = malloc(sizeof(type_mot));
		temp = temp->suivant;
		temp->suivant = NULL;
		
		arg = arg->parent;
		
		temp->lettre = arg->code;
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
