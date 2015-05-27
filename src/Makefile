#DELAPORTE Adrien
#DUNAND Quentin
#NAVARRO Elsa
#POPEK Florian

FLAG = -DDEBUG

all: prog

prog: main.o
	gcc main.o -o main
	
main.o : Main.c
	gcc -c Main.c -o main.o $(FLAG)
	
#Supprimer les .o
clean:
	rm *.o
	
#Supprimer l'éxécutable
mrproprer: clean
	rm main
	rm *.o
