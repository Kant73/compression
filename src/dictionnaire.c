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

void inserer(type_mot* mot, type_dico* dico)
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

int chercher(type_mot* mot, type_dico* dico)
{
	if (dico == NULL || mot == NULL) //Dico ou mot vide
		return;
		
	type_mot* temp_mot = mot;
	type_dico* temp_dico = dico;
	while (temp_mot != NULL)
	{
		if (temp_dico->branches[temp_mot->lettre]->suivant != NULL)
			temp_dico = temp_dico->branches[temp_mot->lettre]->suivant;
		else
			return 0;	
		temp_mot = temp_mot->suivant;
	}

	return 1;
}

void afficher(type_dico* dico)
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
			afficher(dico->branches[i]->suivant);
	}
}




