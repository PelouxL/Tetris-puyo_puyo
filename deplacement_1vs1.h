#ifndef _DEPLACEMENT_1VS1_
#define _DEPLACEMENT_1VS1_
#include "types.h"

/*-------------------- j1 --------------------------*/

void pivot_droit_j1(c_poyo *p, grille *gr);

void pivot_gauche_j1(c_poyo *p, grille *gr);

void deplacement_droit_j1( c_poyo *p, grille *gr);

void deplacement_gauche_j1( c_poyo *p, grille *gr);

void deplacement_bas_j1( c_poyo *p, grille *gr);

void deplacement_j1(c_poyo *p, grille *gr);

c_poyo sauvegarde_poyos_j1(c_poyo *tpoyo, c_poyo poyo_sauvegarde, grille *gr );

/* -------------------- j2 --------------------------*/

void pivot_droit_j2(c_poyo *p, grille *gr);

void pivot_gauche_j2(c_poyo *p, grille *gr);

void deplacement_droit_j2( c_poyo *p, grille *gr);

void deplacement_gauche_j2( c_poyo *p, grille *gr);

void deplacement_bas_j2( c_poyo *p, grille *gr);

void deplacement_j2(c_poyo *p, grille *gr);

c_poyo sauvegarde_poyos_j2(c_poyo *tpoyo, c_poyo poyo_sauvegarde, grille *gr );

#endif
