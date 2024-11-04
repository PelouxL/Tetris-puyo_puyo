#ifndef _INI_POYO_H_
#define _INI_POYO_H_
#include "types.h"

/*------------------ initialisation des poyos -------------*/
void affiche_c_poyo(c_poyo * cp);

void ini_poyo_chaine(c_poyo *tpoyo, int n);

void initialisation_cpoyo(c_poyo * cp);

void apparition_piece(c_poyo * p, grille *gr);

void decalage_gauche(c_poyo *tpoyo, int n);

void roulement_poyo(c_poyo *tpoyo, grille *gr, int n);
/*------------------ fin d'initialisation ----------------*/

#endif