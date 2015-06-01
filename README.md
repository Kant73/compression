# Projet PLS - Compression & Décompression LZW
##Adrien Delaporte - Quentin Dunand - Elsa Navarro - Florian Popek


#Présentation du sujet

Ce projet a été réalisé dans le cadre de la mise en pratique de nos connaissances en C pour la programmation système.

Il consiste à réaliser un utilitaire permettant la compression et la décompression d'un fichier grâce à l'algorithme LZM.

Notre utilitaire produit un fichier compressé à partir d'un fichier original qui ne l'ai pas afin de gagner de l'espace mémoire sur le dique dur. Notre utilitaire est également capable de décompresser un fichier compressé afin de le rendre à nouveau lisible.

#Choix de conception
##Structures de données
###Dictionnaire:

###Mot:


##Fonctions



#Choix de programmation et organisation logicielle
Nous avons découpé notre code en plusieurs modules : Dictionnaire, Compression et Décompression. Ce découpage aurait pu être différent, mais il se justifie comme suit.

##Dictionnaire
Ce fichier contient toutes les fonctions permettant de manipuler un dictionnaire. Par manipulation nous entendons intialisation, vidage, insertion d'un élément, chercher un élément dans le dictionnaire, afficher un dictionnaire et enfin libérer la mémoire occupé par un dictionnaire.

La définition des structures de données utilisées sont aussi présente dans ce fichier car tout l'algorithme LZW repose sur l'utilisation d'un dictionnaire et donc depend de la structure de données que l'on a choisi.

##Compression
Notre module compression contient l'algorithme de compression LZW.

##Decompression


#TODO:
###Dictionnaire:
- Vérifier fonctions pour la décompression
- Commenter le code
- Cleaner le code


###Compression:
- Tester la compression sur des plus gros fichiers et des fichiers de type différents
- Commenter le code
- Cleaner le code

###Decompression:
- Finir l'algo
- Tester l'algo
- Commenter le code


###Rapport:
- Faire le rapport ^^
