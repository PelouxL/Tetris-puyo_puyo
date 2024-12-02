#include <stdlib.h>
#include <stdio.h>
#include "types.h"

/* void aff_grille(grille gr){ */
/*   int i,j; */
/*   for(i = 0 ; i < gr.n ; i++){ */
/*     for(j = 0 ; j < gr.m ; j++){ */
/*       printf("%d ", gr.mat[i][j]); */
/*     } */
/*     printf("\n"); */
/*   } */
/* } */

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




