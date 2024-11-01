#include <stdlib.h>
#include <stdio.h>
#include "types.h"

void initialisation_cpoyo(c_poyo * cp){
  /* 0 = vide , 1 = red, 2 = green, 3 = blue */
  cp -> p1.couleur = (rand()%3)+1;
  cp -> p2.couleur = (rand()%3)+1;
  cp -> p1.x = 0; 
  cp -> p1.y = 0;
  cp -> p1.pos = 0;
  cp -> p2.x = -1;
  cp -> p2.y = -1;
  cp -> p2.pos = 0;

}
/* est appeler une fois lors de la premire apparition d'un poyo */
void apparition_piece(c_poyo * p, grille *gr){
  p -> p1.y = gr -> m/2;
  p -> p2.y = gr -> m/2;
  gr -> mat[p -> p1.x][p -> p1.y]= p -> p1.couleur;
}

int est_dessous(poyo p, grille gr){
  if(gr.mat[p.x][p.y+1] != 0){
    return 1;
  }
  return 0;
}


void avancement_piece(c_poyo * p, grille *gr){
  
  if( gr -> mat[p-> p1.x][p -> p1.y +1] == 0 || p -> p1.y < gr -> m ){
    gr -> mat[p -> p1.x][p -> p1.y] = 0;
    p -> p1.x += 1;
    gr -> mat[p -> p1.x][p -> p1.y] = p -> p1.couleur;
  }else{
    p -> p1.pos = 1;
  }
  
  if( gr -> mat[p-> p2.x][p -> p2.y +1] == 0 || p -> p2.y < gr -> m ){
    gr -> mat[p -> p2.x][p -> p2.y] = 0;
    p -> p2.x += 1;
    gr -> mat[p -> p2.x][p -> p2.y] = p -> p2.couleur;
  }else{
    p -> p2.pos = 0;
  }
}
  
