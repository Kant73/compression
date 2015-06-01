/**
 *	Projet CPS - Compression LZW
 *	@author Adrien DELAPORTE - Quentin DUNAND - Elsa NAVARRO - Florian POPEK
 *	@file decompression.h
 *	@date 2015
 */

/**
 * @brief Algorithme de décodage du fichier d'entrée dans le fichier de sortie
 * @param E fichier d'entree
 * @param S fichier de sortie compresse
 * @param dictionnaire dico
 */
void decode(FILE* E, FILE* S);


void ecrire_lettre(FILE* S, type_mot* mot);