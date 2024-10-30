CC= gcc
OPTION= -W -Wall -pedantic -std=c89 -O2

main: main.o grille.o pieces.o affichage_mlv.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` main.o grille.o pieces.o affichage_mlv.o `pkg-config --libs-only-l MLV` -o main 

main.o: main.c
	$(CC) $(OPTION) main.c -c

grille.o: grille.c
	$(CC) $(OPTION) grille.c -c

pieces.o: pieces.c
	$(CC) $(OPTION) pieces.c -c

affichage_mlv.o: affichage_mlv.c
	$(CC) $(OPTION) affichage_mlv.c -c

clean:
	rm -rf *.o *~  main 
