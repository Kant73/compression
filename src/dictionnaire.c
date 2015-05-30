#include "../include/dictionnaire.h"
#include <math.h>

void initialiser_dico(type_dico* dico, enum type_enum m)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (dico == NULL)
		{
			printf("XXX_BUG_XXX: dico == NULL dans initialiser_dico() ...\n");
			return;
		}
	#endif

	mode = m;
	cpt = 259;

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

void vider_dico(type_dico* dico, int* taille_code)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (dico == NULL)
		{
			printf("XXX_BUG_XXX: dico == NULL dans vider_dico() ...\n");
			return;
		}
	#endif

	int i;
	cpt = 259;
	*taille_code = 9;

	for (i = 0; i < 256; i++)
	{
		liberer_dico(dico->branches[i]->suivant);
		dico->branches[i]->suivant = NULL;
	}

	if (mode == DECOMP)
	{
		liberer_tableau();

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

	#ifdef DEBUG
		printf("___Dictionnaire vidé___\n");
	#endif
}

void inserer_dico(type_mot* mot, type_dico* dico, int* taille_code, FILE* S)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (dico == NULL)
		{
			printf("XXX_BUG_XXX: dico == NULL dans inserer_dico() ...\n");
			return;
		}
		if (mot == NULL)
		{
			printf("XXX_BUG_XXX: mot == NULL dans inserer_dico() ...\n");
			return;
		}
		if (mot->suivant == NULL)
		{
			printf("XXX_BUG_XXX: mot possède qu'une seule lettre, pas besoin d'insérer ...\n");
			return;
		}
	#endif

	type_dico* temp_dico = dico;
	type_mot* temp_mot = mot;
	
	while (temp_mot->suivant != NULL)
	{
		if (temp_dico->branches[temp_mot->lettre]->suivant == NULL)
		{
			temp_dico->branches[temp_mot->lettre]->suivant = calloc(1, sizeof(type_dico));
			temp_dico->branches[temp_mot->lettre]->suivant->parent = malloc(sizeof(type_cellule));
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

	#ifdef DEBUG
		printf("\tMot ajouté (code %d): ", cpt);
		afficher_mot(mot);
	#endif

	cpt++; //On incrémente le compteur
	
	if (cpt == (int)(pow(2, (double)(*taille_code)) - 1))
	{
		if (cpt == 16384 - 1)
		{
			paquet8_ecrire(258, *taille_code, S);
			vider_dico(dico, taille_code);
		}
		else
		{
			#ifdef DEBUG
				printf("\t\tTaille des codes: %d -> %d\n", cpt, cpt+1);
			#endif

			paquet8_ecrire(257, *taille_code, S);
			(*taille_code) ++;
		}
	}
}

void ajouter_element(uint8_t i, type_dico* d)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (d == NULL)
		{
			printf("XXX_BUG_XXX: d == NULL dans ajouter_element(), référence vers un dictionnaire indéfinie ...\n");
			return;
		}
	#endif

	type_cellule c;
	c.indice = i;
	c.dico_contenant = d;

	tableau[cpt/4096][cpt - cpt/4096] = c;
}

type_mot* chercher_mot_dico(int code, type_dico* dico)
{
	if (dico == NULL)
		return;

	return mot_associe(tableau[code/4096][code%4096].dico_contenant, tableau[code/4096][code%4096].indice);
}

int chercher_code_dico(type_mot* mot, type_dico* dico)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (dico == NULL)
		{
			printf("XXX_BUG_XXX: dico == NULL dans chercher_code_dico() ...\n");
			return -1;
		}
		if (mot == NULL)
		{
			printf("XXX_BUG_XXX: mot == NULL dans chercher_code_dico() ...\n");
			return -1;
		}
	#endif
		
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
	if (dico == NULL)
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
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (mot == NULL)
		{
			printf("XXX_BUG_XXX: mot == NULL dans liberer_mot() ...\n");
			return;
		}
	#endif

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
	free(dico->parent);
	free(dico);
}

void liberer_tableau()
{
	int i, j;
	for (i = 0; i < 16; i++)
	{
		if (tableau[i] != NULL)
		{
			for (j = 0; j < 4096; j++)
				free(tableau[i] + j);
		}
	}
}

void paquet8_ecrire(int code, int taille, FILE* S)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (taille <= 8)
		{
			printf("XXX_BUG_XXX: taille == %d dans paquet8_ecrire() ...\n", taille);
			return;
		}
	#endif

	//Initialisation des statics
	static uint8_t buffer_s = 0;
	static int taille_s = 0;
	
	//////////////
	uint8_t temp; //Valeur à retourner

	if (taille_s > 0) //Si le buffer n'est pas vide
	{
		temp = (code >> (taille - 8 + taille_s)) + buffer_s;
		fprintf(S, "%c", temp);	//Ecrire dans le fichier le mot temp

		taille = taille - 8 + taille_s;
	}
	
	taille_s = 0;
	buffer_s = 0;

	while (taille >= 8)
	{
		temp = code >> (taille - 8);
		fprintf(S, "%c", temp); //Ecrire dans le fichier le mot temp
		
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

int paquet8_lire(int taille, FILE* S)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (taille <= 8)
		{
			printf("XXX_BUG_XXX: taille == %d dans paquet8_lire() ...\n", taille);
			return -1;
		}
	#endif
		
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

		int temp2 = fgetc(S);
		temp2 = temp2 << (taille - 8);
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
	
	#ifdef DEBUG
		printf("paquet8_lire:\n");
		printf("\tTaille buffer: %d\n", taille_s);
		printf("\tBuffer: %s\n", to_binaire(buffer_s));
	#endif

	return result;
}

char * to_binaire(unsigned long int arg)
{
	//Tiré de "developpez.net": http://www.developpez.net/forums/d7914/c-cpp/c/afficher-nombre-binaire-printf/
    static char buffer [1+sizeof (unsigned long int)*8] = { 0 };
    char *p=buffer-1+sizeof (unsigned long int)*8;
    do { *--p = '0' + (arg & 1); arg >>= 1; } while (arg);
    return p;
}

void affecter_mot(type_mot* mot1, type_mot* mot2)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (mot1 = NULL)
		{
			printf("XXX_BUG_XXX: mot1 == NULL dans affecter_mot() ...\n");
			return;
		}
		if (mot2 = NULL)
		{
			printf("XXX_BUG_XXX: mot2 == NULL dans affecter_mot() ...\n");
			return;
		}
	#endif

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
		temp->suivant = NULL;

		temp->lettre = mot2->lettre;
		mot2 = mot2->suivant;
	}	
}

void afficher_mot(type_mot* mot)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (mot = NULL)
		{
			printf("XXX_BUG_XXX: mot == NULL dans afficher_mot() ...\n");
			return;
		}
	#endif

	do
	{
		printf("%c", mot->lettre);
		mot = mot->suivant;
	} while (mot != NULL);

	printf("\n");
}

type_mot* mot_associe(type_dico* dico, uint8_t indice)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (dico = NULL)
		{
			printf("XXX_BUG_XXX: dico == NULL dans mot_associe() ...\n");
			return;
		}
	#endif
		
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
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (mot = NULL)
		{
			printf("XXX_BUG_XXX: mot == NULL dans inserer_queue_mot() ...\n");
			return;
		}
	#endif

	type_mot* temp_mot = mot;
	while (temp_mot->suivant != NULL)
		temp_mot = temp_mot->suivant;
		
	temp_mot->suivant = malloc(sizeof(type_mot));
	temp_mot->suivant->lettre = elem;
	temp_mot->suivant->suivant = NULL;
}

void init_mot(type_mot* mot, uint8_t val_init)
{
	#ifdef DEBUG //Mauvaise utilisation de la fonction
		if (mot = NULL)
		{
			printf("XXX_BUG_XXX: mot == NULL dans init_mot() ...\n");
			return;
		}
	#endif
		
	mot->lettre = val_init;
	mot->suivant = NULL;

	#ifdef DEBUG
		printf("Caractère récupéré du fichier: %c\t%s\n", val_init, to_binaire(val_init));
	#endif
}
