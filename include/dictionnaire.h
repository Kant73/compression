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
	type_dico* parent;
};

struct type_mot
{
	uint8_t lettre;
	type_mot* suivant;
};

/**
 * Initialise le dictionnaire avec les monomes
 * @param dico [description]
 */
void initialiser_dico(type_dico* dico);

/**
 * Insere un mot dans le dictionnaire
 * @param mot  [description]
 * @param dico [description]
 */
void inserer_dico(type_mot* mot, type_dico* dico);

/**
 * Cherche si un mot existe dans le dictionnaire
 * @param  mot  [description]
 * @param  dico [description]
 * @return      -1 si pas dedans / le code du mot sinon
 */
int chercher_code_dico(type_mot* mot, type_dico* dico);

/**
 * Affiche le contenu du dictionnaire
 * @param dico [description]
 */
void afficher_dico(type_dico* dico);

/**
 * Libérer la mémoire occupée par un mot
 * @param mot [description]
 */
void liberer_mot(type_mot* mot);

/**
 * Libérer la mémoire occupée par un dictionnaire
 * @param dico [description]
 */
void liberer_dico(type_dico* dico);

/**
 * Renvoie la liste des paquets de 8 bits
 * @param  code   [description]
 * @param  taille [description]
 * @return        [description]
 */
type_mot* paquet8(int code, int taille);

/**
 * Renvoie le nombre de bits significatifs
 * @param  code [description]
 * @return      [description]
 */
int nbr_bit(int code);

/**
 * [inserer_queue_mot description]
 * @param mot  [description]
 * @param elem [description]
 */
void inserer_queue_mot(type_mot* mot, uint8_t elem);

/**
 * Initialise un nouveau mot avec la valeur val_init et affecte son pointeur suivant à NULL
 * @param mot      Le mot qu'on veut initialiser
 * @param val_init La valeur que l'on va affecter à l'attribut lettre du mot "mot"
 */
void init_mot(type_mot* mot, uint8_t val_init);
