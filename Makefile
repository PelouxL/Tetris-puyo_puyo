CC= gcc
OPTION= -W -Wall -pedantic -std=c89 -O2

main: main.o grille.o
	$(CC) $(OPTION) main.o grille.o -o main 

main.o: main.c
	$(CC) $(OPTION) main.c -c

grille.o: grille.c
	$(CC) $(OPTION) grille.c -c

clean:
	rm -rf *.o *~ main 
