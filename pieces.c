#include <stlib.h>
#include <stdio.h>
#include "types.h"

void initialisation(piece * pi){
  /* 0 = vide , 1 = red, 2 = green, 3 = blue */
  pi->gauche = (rand()%3)+1;
  pi->droit = (rand()%3)+1;
  pi->larg = (rand%2)+1;
  if(pi->larg == 2){ /*  definit si la piece est horizontale ou vertical */
    pi->haut = 1;
  }else{
    pi->haut = 2;
  }
  pi->x = 0;
  pi->y = 0;
}
