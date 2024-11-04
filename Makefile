CC= gcc
OPTION= -W -Wall -pedantic -std=c89 -O2

main: main.o grille.o pieces.o affichage_mlv.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -o $@

main.o: main.c
	$(CC) $(OPTION) $^ -c

grille.o: grille.c
	$(CC) $(OPTION) $^ -c

pieces.o: pieces.c
	$(CC) $(OPTION) $^ -c

affichage_mlv.o: affichage_mlv.c
	$(CC) $(OPTION) $^ -c

clean:
	rm -rf *.o *#~  main 
