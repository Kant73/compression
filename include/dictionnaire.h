#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define _TAILLE_ 32768

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


/**
 * Initialise le dictionnaire, m pour compression ou décompression
 * @param dico Le dictionnaire qu'on veut initialiser
 * @param m    Le mode d'initialisation : compression ou décompression
 */
void initialiser_dico(type_dico* dico, enum type_enum m);


/**
 * Vide le dictionnaire
 * @param dico        Le dico que l'on veut vider
 * @param taille_code La taille du code
 */
void vider_dico(type_dico* dico, int* taille_code);


/**
 * Insère un mot dans le dictionnaire. Génère le code associé et change la taille du code si nécessaire (ex: cpt = 511, taille_code = 9 -> taille_code = 10)
 * @param mot         Le mot qu'on veut inserer dans le dico
 * @param dico        Le dico dans lequel on veut inserer un mot
 * @param taille_code La taille du code
 * @param S           Le fichier de sortie pour la compression ou la décompression
 */
void inserer_dico(type_mot* mot, type_dico* dico, int* taille_code, FILE* S);

/**
 * Ajoute un élément dans le tableau des codes (exclusif décompression)
 */
void ajouter_element(uint8_t i, type_dico* d);


/**
 * Recherche le code associé à un mot
 * @param  mot  Le mot qu'on cherche dans le dico
 * @param  dico Le dico dans lequel on cherche des éléments
 * @return      Le code du mot recherché, -1 si il n'est pas trouvé
 */
int chercher_code_dico(type_mot* mot, type_dico* dico);


/**
 * Recherche le mot associé à un code
 * @param  code Le code dont on veut le mot associé
 * @param  dico Le dico danq lequel on cherche le mot
 * @return      Le mot associé au code
 */
type_mot* chercher_mot_dico(int code, type_dico* dico);


/**
 * Affiche le dictionnaire (récursif)
 * @param dico Le dico qu'on veut afficher
 */
void afficher_dico(type_dico* dico);


/**
 * Affiche le tableau
 */
void afficher_tableau();


/**
 * Permet de libérer un mot de la mémoire
 * @param mot Le mot que l'ont veut libérer de la mémoire
 */
void liberer_mot(type_mot* mot);


/**
 * Permet de libérer un dictionnaire (récursif)
 * @param dico Le dico qu'on veut libérer de la mémoire
 */
void liberer_dico(type_dico* dico);



/**
 * Libérer le tableau (exclusif à la décompression)
 */
void liberer_tableau();


/**
 * Ecrit dans le fichier les octets, mémorise les bits restants
 * @param code   Le code qu'on veut écrire dans le fichier
 * @param taille La taille du code
 * @param S      Le fichier dans lequel on veut écrire
 */
void paquet8_ecrire(int code, int taille, FILE* S);


/**
 * Lit dans le fichier les octets, mémorise les bits restants
 * @param  taille La taille qu'on veut lire
 * @param  S      Le fichier dans lequel on lit
 * @return        Les octets qu'on veut ecrire
 */
int paquet8_lire(int taille, FILE* S);


/**
 * Remonte le dictionnaire pour chercher le mot associé
 * @param  dico   Le dictionnaire qu'on remonte
 * @param  indice L'indice du mot qu'on cherche
 * @return        Le mot associé à l'indice
 */
type_mot* mot_associe(type_dico* dico, uint8_t indice);

/**
 * Concatène un élément à un mot
 * @param mot  Le mot au quel on veut concatener un élément
 * @param elem L'élément qu'on veut concatener au mot
 */
void inserer_queue_mot(type_mot* mot, uint8_t elem);

/**
 * Permet de printf en binaire (%s)
 * @param  arg La variable qu'on veut printf en binaire
 * @return     Une chaine qui contient l'écriture binaire de notre variable
 */
char* to_binaire(unsigned long int arg);

//mot1 <- mot2
/**
 * Permet d'affecter au mot1 les valeurs du mot2
 * @param mot1 Le mot dont on veut changer les valeurs
 * @param mot2 Le mot dont on copie les valeurs
 */
void affecter_mot(type_mot* mot1, type_mot* mot2);

/**
 * Permet d'affiche un mot
 * @param mot Le mot qu'on veut afficher
 */
void afficher_mot(type_mot* mot);
