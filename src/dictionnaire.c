#include "../include/dictionnaire.h"
#include <math.h>

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
	}
}

void inserer_dico(type_mot* mot, type_dico* dico)
{
	static int cpt = 256;
	
	if (dico == NULL || mot == NULL || mot->suivant == NULL) //Dico ou mot vide
		return;
	
	type_dico* temp_dico = dico;
	type_mot* temp_mot = mot;
	
	while (temp_mot->suivant != NULL)
	{
		if (temp_dico->branches[temp_mot->lettre]->suivant == NULL)
			temp_dico->branches[temp_mot->lettre]->suivant = calloc(1, sizeof(type_dico*));
		
		temp_dico = temp_dico->branches[temp_mot->lettre]->suivant;
		temp_mot = temp_mot->suivant;
	}

	temp_dico->branches[temp_mot->lettre] = malloc(sizeof(type_code));
	temp_dico->branches[temp_mot->lettre]->code = cpt;
	temp_dico->branches[temp_mot->lettre]->suivant = NULL;

	cpt++;
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
			
			temp_mot = temp_mot->suivant;
			temp_dico = temp_dico->branches[temp_mot->lettre]->suivant;
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
			afficher_dico(dico->branches[i]->suivant);
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
	return log(code) / log(2);
}

type_mot* paquet8(int code, int taille)
{
	static uint8_t buffer_s = 0;
	static int taille_s = 0;
	
	type_mot* liste = malloc(sizeof(type_mot));
	type_mot* temp = liste;

	if (taille + taille_s >= 8)
	{
		temp->lettre = code >> (taille - 8 + taille_s);
		uint8_t mask = -1;
		mask = ~(mask << (8 - taille_s));
		temp->lettre = (temp->lettre & mask) + buffer_s; 
		
		taille = taille - 8 + taille_s;
		if (taille >= 8)
		{
			temp->suivant = malloc(sizeof(type_mot));
			temp = temp->suivant;
			temp->suivant = NULL;
		}
	}
	
	taille_s = 0;
	buffer_s = 0;

	while (taille >= 8)
	{
		temp->lettre = code >> (taille - 8);
		taille = taille - 8;
		if (taille >= 8)	
		{
			temp->suivant = malloc(sizeof(type_mot));
			temp = temp->suivant;
			temp->suivant = NULL;
		}
	}
	
	if (taille > 0)
	{
		taille_s = taille;
		
		buffer_s = code;
		buffer_s = buffer_s << (8 - taille_s);
		printf("Taille: %d\n", taille);
		printf("Buffer: %x\n", buffer_s);
	}
	
	return liste;
}
