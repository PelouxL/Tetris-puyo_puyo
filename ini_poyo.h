#ifndef _INI_POYO_H_
#define _INI_POYO_H_
#include "types.h"

/*------------------ initialisation des poyos -------------*/
void affiche_c_poyo(c_poyo * cp);

void ini_poyo_chaine(tc_poyo *tpoyo);

void initialisation_cpoyo(c_poyo * cp);

void initialisation_cpoyo_vide(c_poyo *cp);

void apparition_piece(c_poyo * p, grille *gr);

void decalage_gauche(tc_poyo *tpoyo, int n);

void roulement_poyo(tc_poyo *tpoyo, grille *gr);

/*------------------ fin d'initialisation ----------------*/

#endif
