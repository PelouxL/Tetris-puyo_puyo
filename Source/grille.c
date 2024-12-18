#ifndef _GRILLE_C_
#define _GRILLE_C_
#include <stdlib.h>
#include <stdio.h>
#include "types.h"

/* affiche grille sur terminal */
void aff_grille(grille gr){
  int i,j;
  for(i = 0 ; i < gr.n ; i++){
    for(j = 0 ; j < gr.m ; j++){
      printf("%d ", gr.mat[i][j]);
    }
    printf("\n");
  }
}

/* initialise la structure de la grille */
grille initialisation_grille( int n, int m){
  int i, j;
  grille gr;
  gr.n = n;
  gr.m = m;
  gr.niveau = 1;
  for(i = 0 ; i < n ; i++){
    for(j = 0 ; j < m ; j++){
      gr.mat[i][j] = 0;
    }
  }
  return gr;
}

#endif


