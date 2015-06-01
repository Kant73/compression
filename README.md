
# <center>Projet PLS - Compression & Décompression LZW</center>

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
Notre module compression contient l'algorithme de compression LZW. Il utilise toutes les fonctions implémentées dans le module dictionnaire.

##Decompression
Notre module decompression contient l'algorithme de decompression LZW. Il utilise toutes les fonctions implémentées dans le module dictionnaire.


#Compilation et utilisation
##Compilation
Pour compiler le programme, il suffit de se rendre dans le dossier `/src`, d'ouvrir un terminal et d'exécuter la commande `make` qui va générer un exécutable nommé "LZW".

Exemple :
```
quentin@quentin-S301LA:~/Documents/polytech/cps/compression/src$ make
gcc -c Main.c -o main.o -I ../include -w -lm -O3
gcc -c compression.c -o compression.o -I ../include -w -lm -O3
gcc -c decompression.c -o decompression.o -I ../include -w -lm -O3
gcc -c dictionnaire.c -o dictionnaire.o -I ../include -w -lm -O3
gcc main.o dictionnaire.o compression.o decompression.o -o LZW -w -lm -O3
```

Si il est nécessaire de nettoyer le dossier `/src`, deux commandes sont prévues à cet effet :
`make clean` et `make mrproper`.

La première commande s'occupe uniquement de supprimer les fichiers `.o` alors que la deuxième supprime les fichiers `.` ainsi que les exécutables ayant pu être générés dans le dossier `src\`.

##Utilisation
Afin d'utiliser le programme, il suffit d’exécuter la commande suivante :

Pour compresser: `./LZW -c <fichier_a_compresser> <fichier_compressé>`

Pour décompresser:`./LZW -d <fichier_a_décompresser> <fichier_décompressé>`

Par exemple : `./LZW -c image.bmp image_compressée`

#Exemple d'exécution
##Compression

##Décompression

#Extensions
##Lecture/écriture binaire des codes
Nous avons réaliser une écriture/lecture binaire des codes issu de la compression/décompression avec l'algorithme LZW. Ceci permet de réaliser une vraie compression des fichiers que l'on passe en paramètre à notre utilitaire.

##Versions plus efficace
Notre utilitaire est compilé en utilisant le flag -O3 afin d'optimiser le mieux possible l'éxecution de notre code.

##Ré-initialisation partielle ou totale du dictionnaire
Notre dictionnaire est réinitialiser quand sa taille atteint 2<sup>19</sup> élements. En effet, nous avons choisi cette taille car après avoir fais de nombreuses analyses, nous avons déterminé que le niveau de compression stagnais avec des dictionnaire plus importants, comme vous pouvez le voir avec le graphique ci-dessous.

#Documentation
Le code source de ce projet est entièrement commenté. Néanmoins, une documentation Doxygen a tout de même été générée afin d'obtenir une documentation plus propre et permettant de trouver plus facilement les différentes définitions des fonctions que nous avons implémentées.

Cette documentation Doxygen est consultable avec le chemin suivant : `\doc\html\index.html`
