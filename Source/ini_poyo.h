#ifndef _INI_POYO_H_
#define _INI_POYO_H_
#include "types.h"

/* affiche la structure dun poyo sur le terminal */
void affiche_c_poyo(c_poyo * cp);

/* initialise le tpoyo */
void ini_poyo_chaine(c_poyo *tpoyo, int n);

/* initialise la structure d'un poyo */
void initialisation_cpoyo(c_poyo * cp);

/* initialise la structure d'un poyo vide */
void initialisation_cpoyo_vide(c_poyo *cp);

/* fais un decalage a gauche du tpoyo */
void decalage_gauche(c_poyo *tpoyo, int n);

/* fais la creation du poyo 4 et le decalage */
void roulement_poyo(c_poyo *tpoyo, grille *gr);

#endif