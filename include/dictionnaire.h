#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct type_dico type_dico;
typedef struct type_code type_code;
typedef struct type_mot type_mot;

struct type_dico
{
	type_code* branches[256];
};

struct type_code
{
	int code;
	type_dico* suivant;
};

struct type_mot
{
	uint8_t lettre;
	type_mot* suivant;
};

//Initialise le dictionnaire avec les monomes
void initialiser_dico(type_dico* dico);

//Insere un mot dans le dictionnaire
void inserer_dico(type_mot* mot, type_dico* dico);

//Cherche si un mot existe dans le dictionnaire (@return: -1 si pas dedans / le code du mot sinon)
int chercher_dico(type_mot* mot, type_dico* dico);

//Affiche le contenu du dictionnaire
void afficher_dico(type_dico* dico);

//Libérer la mémoire occupée par un mot
void liberer_mot(type_mot* mot);

//Libérer la mémoire occupée par un dictionnaire
void liberer_dico(type_dico* dico);
