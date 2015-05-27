typedef struct type_dico type_dico;
struct type_dico
{
	type_dico* branches[256];
};

typedef struct type_mot type_mot;
struct type_mot
{
	uint8_t lettre;
	type_mot* suivant;
};

//Initialise le dictionnaire avec les monomes
void initialiser();

//Insere un mot dans le dictionnaire
void inserer(type_mot* mot, type_dico* dico);

//Cherche si un mot existe dans le dictionnaire (@return: 0 si pas dedans / 1 si dedans)
int chercher(type_mot* mot, type_dico* dico);


