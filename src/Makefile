#DELAPORTE Adrien
#DUNAND Quentin
#NAVARRO Elsa
#POPEK Florian

FLAG = -DDEBUG

all: prog

prog: main.o fonctions.o compression.o decompression.o dictionnaire.o
	gcc main.o -o main
	
main.o : Main.c ../include/*.h
	gcc -c Main.c -o main.o -I ../include $(FLAG)
	
fonctions.o: Fonctions.c ../include/*.h
	gcc -c Fonctions.c -o fonctions.o -I ../include $(FLAG)

compression.o : compression.c ../include/*.h
	gcc -c compression.c -o compression.o -I ../include $(FLAG)

decompression.o : decompression.c ../include/*.h
	gcc -c decompression.c -o decompression.o -I ../include $(FLAG)
	
dictionnaire.o : dictionnaire.c ../include/*.h
	gcc -c dictionnaire.c -o dictionnaire.o -I ../include $(FLAG)
	
#Supprimer les .o
clean:
	rm -rf *.o
	rm -rf *~
	rm -rf ../include/*~
	rm -rf ../*~
	
#Supprimer l'éxécutable
mrproprer: clean
	rm main
	
