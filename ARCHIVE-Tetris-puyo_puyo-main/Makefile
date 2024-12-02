CC= gcc
OPTION= -W -Wall -pedantic -std=gnu89 -O3

main: main.o grille.o pieces.o affichage_mlv.o ini_poyo.o destruction.o jeu.o menu.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -lrt -o $@

main.o: main.c
	$(CC) $(OPTION) $^ -c

grille.o: grille.c
	$(CC) $(OPTION) $^ -c

pieces.o: pieces.c
	$(CC) $(OPTION) $^ -c

affichage_mlv.o: affichage_mlv.c
	$(CC) $(OPTION) $^ -c

ini_poyo.o: ini_poyo.c
	$(CC) $(OPTION) $^ -c

destruction.o: destruction.c
	$(CC) $(OPTION) $^ -c

jeu.o: jeu.c
	$(CC) $(OPTION) $^ -c

menu.o: menu.c
	$(CC) $(OPTION) $^ -c

clean:
	rm -rf *.o *#~  main 
