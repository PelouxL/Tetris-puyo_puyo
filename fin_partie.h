#ifndef _FIN_PARTIE_H_
#define _FIN_PARTIE_H_
#include "types.h"

int verif_fin( c_poyo poyo, grille gr );

int fin_solo( c_poyo poyo, joueur je, grille gr );

int fin_1vs1( c_poyo poyo1, c_poyo poyo2, joueur je1, joueur je2, grille gr1, grille gr2);

#endif
