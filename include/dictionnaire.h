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
int chercher_code_dico(type_mot* mot, type_dico* dico);

//Affiche le contenu du dictionnaire
void afficher_dico(type_dico* dico);

//Libérer la mémoire occupée par un mot
void liberer_mot(type_mot* mot);

//Libérer la mémoire occupée par un dictionnaire
void liberer_dico(type_dico* dico);

//Renvoie la liste des paquets de 8 bits
type_mot* paquet8(int code, int taille);

//Renvoie le nombre de bits significatifs
int nbr_bit(int code);

//Insère en queue d'un type_mot un élement de type uint8_t
void inserer_queue_mot(type_mot* mot, uint8_t elem)
