#ifndef _FIN_PARTIE_H_
#define _FIN_PARTIE_H_
#include "types.h"

/* verifie si la partie est terminee */
int verif_fin( c_poyo poyo, grille gr );

/* permet de finir une partie et de mettre a jour le tableau score */
int fin_solo( c_poyo poyo, joueur je, grille gr, int dest );

int fin_1vs1( c_poyo poyo1, c_poyo poyo2, joueur je1, joueur je2, grille gr1, grille gr2, int dest1, int dest2);

#endif
