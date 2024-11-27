#ifndef _CHRONO_H_
#define _CHRONO_H_
#include "types.h"

void chronometre(hms * chrono);

void gestion_niveau_grille(grille *gr, hms chrono);

int gestion_vitesse_grille(grille *gr);

#endif
