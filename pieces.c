#include <stdlib.h>
#include <stdio.h>
#include "types.h"

void initialisation(c_poyo * cp){
  /* 0 = vide , 1 = red, 2 = green, 3 = blue */
  cp->p1.couleur = (rand()%3)+1;
  cp->p2.couleur = (rand()%3)+1;
  cp->larg = (rand()%2)+1; /* on definit si couple poyo vertical ou horizntale */
  cp->p1.x = 0; 
  cp->p1.y = 0;
  cp->p2.x = 0;
  cp->p2.y = 0;

}
