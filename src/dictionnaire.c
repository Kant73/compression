#include <stdio.h>
#include <string.h>

#include "../include/dictionnaire.h"

void initialiser()
{
}

void inserer(type_mot* mot, type_dico* dico)
{
}

int chercher(type_mot* mot, type_dico* dico)
{
	if (mot == NULL) //Mot vide
		return 0;
		
	type_mot* temp = mot;
	while (temp != NULL)
	{
		if ((*dico)[temp->lettre] != NULL)
			temp = temp->suivant;
		else
			return 0;
	}

	return 1;
}
