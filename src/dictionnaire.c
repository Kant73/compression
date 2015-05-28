#include "../include/dictionnaire.h"

void initialiser_dico(type_dico* dico)
{
	if (dico == NULL) //Dico vide
		return;
		
	int i;
	for (i = 0; i < 256; i++)
	{
		dico->branches[i] = calloc(1, sizeof(type_code));
		dico->branches[i]->code = i;
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

	temp_dico->branches[temp_mot->lettre] = calloc(1, sizeof(type_code*));
	temp_dico->branches[temp_mot->lettre]->code = cpt;

	cpt++;
}

int chercher_dico(type_mot* mot, type_dico* dico)
{
	if (dico == NULL || mot == NULL) //Dico ou mot vide
		return -1;
		
	type_mot* temp_mot = mot;
	type_dico* temp_dico = dico;
	while (true)
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
		mot = mot_temp->suivant;
		free(mot_temp);
		mot_temp = *mot;
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



