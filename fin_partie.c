#include <stdlib.h>
#include <stdio.h>
#include "types.h"

int verif_fin( c_poyo poyo, grille gr ){
  /* on verifie si un poyo a ete poser a l'endroit de l'initialisation */
  if( (poyo.p1.pos == 1 && ( poyo.p1.x == 0 && poyo.p1.y == gr.m/2 ) ) ||
      ( (poyo.p2.pos == 1 && ( poyo.p2.x == 0 && poyo.p2.y == gr.m/2 )))){
    return 1;
  }
  return 0;
}
	
