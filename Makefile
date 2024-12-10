CC= gcc
OPTION= -W -Wall -pedantic -std=gnu89 -O3

main: main.o grille.o pieces.o affichage_mlv.o ini_poyo.o destruction.o jeu.o chrono.o score.o deplacement_1vs1.o fin_partie.o menu.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -lrt -o $@ -lMLV

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

chrono.o: chrono.c
	$(CC) $(OPTION) $^ -c

score.o: score.c
	$(CC) $(OPTION) $^ -c

deplacement_1vs1.o: deplacement_1vs1.c
	$(CC) $(OPTION) $^ -c

fin_partie.o: fin_partie.c
	$(CC) $(OPTION) $^ -c

menu.o: menu.c
	$(CC) $(OPTION) $^ -c

anim: animation.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -lrt -o $@ -lMLV

animation.o: animation.c
	$(CC) $(OPTION) $^ -c

clean:
	rm -rf *.o *~  main 
