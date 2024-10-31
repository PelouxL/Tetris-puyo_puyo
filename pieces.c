#include <stdlib.h>
#include <stdio.h>
#include "types.h"

void initialisation(c_poyo * cp){
  /* 0 = vide , 1 = red, 2 = green, 3 = blue */
  cp->p1.couleur = (rand()%3)+1;
  cp->p2.couleur = (rand()%3)+1;
  cp->larg = (rand()%2)+1; /* on definit si couple poyo vertical ou horizontale */
  cp->p1.x = 0; 
  cp->p1.y = 0;
  cp->p2.x = 0;
  cp->p2.y = 0;

}

c_poyo apparition_piece(c_poyo * p){
    int vertical, horizontale, vert_ou_horiz;
    vertical = 0;
    horizontale = 1;
    vert_ou_horiz = rand() % 2;
    p -> p1.x = 0;
    p -> p1.y = M / 2;
    p -> p2.x = 0;
    p -> p2.y = M / 2 + 1; /* initialisation des poyos de manière horizontale au début et on regarde après si il est vertical ou horizontale */
    switch(vert_ou_horiz){
    case 0: /* vertical */
        p -> p2.x = p -> p2.x + 1;
        p -> p2.y = M / 2;
        p -> larg = vertical;
        /* on touche pas au poyo 1 qui est au centre et on change le deuxième poyo juste en bas du 1er */
        break;
    case 1: /* horizontale */
        p -> p2.x = p -> p1.x;
        p -> p2.y = p -> p1.y + 1;
        p -> larg = horizontale;
        break;
    }
    return *p;
}

void tourner_p(c_poyo *p){
    