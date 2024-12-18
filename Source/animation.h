#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "types.h"

/* charge les frames de lanimation */
int charger_croix( MLV_Image *croix[NUM_CROIX] );

/* toutes les 15 frames on affiche une nouvelle frame */
void animation_croix( hms chrono, MLV_Image *croix[NUM_CROIX], int x, int y );

#endif

		      
