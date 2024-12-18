#ifndef _CHRONO_H_
#define _CHRONO_H_
#include "types.h"

/* definition d'un chronometre */
void chronometre(hms * chrono);

/* inttialisation du type chrono */
void ini_chrono( hms *chrono);

/* toutes les 30s augmente le niveau de la grille */
void gestion_niveau_grille(grille *gr, hms chrono);

/* accelere la vitesse de jeu */
int gestion_vitesse_grille(grille *gr);

#endif
