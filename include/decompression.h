/*
	Projet CPS - Compression LZW
	Adrien DELAPORTE - Quentin DUNAND - Elsa NAVARRO - Florian POPEK
	decompression.h
 */

/**
 * Algorithme de décodage du fichier d'entrée dans le fichier de sortie
 * @param E fichier d'entree
 * @param S fichier de sortie compresse
 * @param dictionnaire dico
 */
void decode(FILE* E, FILE* S, type_dico* dico);