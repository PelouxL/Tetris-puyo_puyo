CC= gcc
OPTION= -W -Wall -pedantic -std=gnu89 -O3
OBJET= ./Objet/
SOURCE= ./Source/

Puyo_Puyo: $(OBJET)main.o $(OBJET)animation.o $(OBJET)grille.o $(OBJET)pieces.o $(OBJET)affichage_mlv.o $(OBJET)ini_poyo.o $(OBJET)destruction.o $(OBJET)jeu.o $(OBJET)chrono.o $(OBJET)score.o $(OBJET)deplacement_1vs1.o $(OBJET)fin_partie.o $(OBJET)menu.o
	$(CC) $(OPTION) `pkg-config --cflags MLV` `pkg-config --libs-only-other --libs-only-L MLV` $^ `pkg-config --libs-only-l MLV` -lrt -o $@ -lMLV

$(OBJET)main.o: $(SOURCE)main.c
	mkdir -p $(OBJET)
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)grille.o: $(SOURCE)grille.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)pieces.o: $(SOURCE)pieces.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)affichage_mlv.o: $(SOURCE)affichage_mlv.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)ini_poyo.o: $(SOURCE)ini_poyo.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)destruction.o: $(SOURCE)destruction.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)jeu.o: $(SOURCE)jeu.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)chrono.o: $(SOURCE)chrono.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)score.o: $(SOURCE)score.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)deplacement_1vs1.o: $(SOURCE)deplacement_1vs1.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)fin_partie.o: $(SOURCE)fin_partie.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)menu.o: $(SOURCE)menu.c
	$(CC) $(OPTION) $^ -c -o $@

$(OBJET)animation.o: $(SOURCE)animation.c
	$(CC) $(OPTION) $^ -c  -o $@

clean:
	rm -rf $(OBJET) *~  Puyo_Puyo anim
