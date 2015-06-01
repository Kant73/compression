#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define _TAILLE_ 1024

typedef struct type_dico type_dico;
typedef struct type_code type_code;
typedef struct type_mot type_mot;
typedef struct type_cellule type_cellule;

struct type_dico
{
	type_code* branches[256];
	type_cellule* parent;
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

struct type_cellule
{
	uint8_t indice;
	type_dico* dico_contenant;
};

enum type_enum
{
	COMP = 0,
	DECOMP
};

//////////////
////GLOBAL////
//////////////
type_cellule* tableau[16];	//Exclusif décompression
enum type_enum mode; 		//Compression ou décompression
int cpt; 					//Compteur des codes
//////////////

//Initialise le dictionnaire, m pour compression ou décompression
void initialiser_dico(type_dico* dico, enum type_enum m);

//Vide le dictionnaire
void vider_dico(type_dico* dico, int* taille_code);

//Insère un mot dans le dictionnaire. Génère le code associé et change la taille du code si nécessaire (ex: cpt = 511, taille_code = 9 -> taille_code = 10)
void inserer_dico(type_mot* mot, type_dico* dico, int* taille_code, FILE* S);

//Ajoute un élément dans le tableau des codes (exclusif décompression)
void ajouter_element(uint8_t i, type_dico* d);

//Recherche le code associé à un mot
int chercher_code_dico(type_mot* mot, type_dico* dico);
//Recherche le mot associé à un code
type_mot* chercher_mot_dico(int code, type_dico* dico);

//Affiche le dictionnaire (récursif)
void afficher_dico(type_dico* dico);

//Affiche le tabeau
void afficher_tableau();

//Libérer un mot
void liberer_mot(type_mot* mot);
//Libérer le dictionnaire (récursif)
void liberer_dico(type_dico* dico);
//Libérer le tableau (exculisf décompression)
void liberer_tableau();

//Ecrit dans le fichier les octets, mémorise les bits restants
void paquet8_ecrire(int code, int taille, FILE* S);
//Lit dans le fichier les octets, mémorise les bits restants
int paquet8_lire(int taille, FILE* S);

//Remonte le dictionnaire pour chercher le mot associé
type_mot* mot_associe(type_dico* dico, uint8_t indice);

//Concatène un élément à un mot
void inserer_queue_mot(type_mot* mot, uint8_t elem);

//Permet de printf en binaire (%s)
char* to_binaire(unsigned long int arg);

//mot1 <- mot2
void affecter_mot(type_mot* mot1, type_mot* mot2);
//Affiche un mot
void afficher_mot(type_mot* mot);
