#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>
#define TCUB 50

void aff_jeu(){
  MLV_clear_window(MLV_COLOR_YELLOW3);
}

void aff_etat(grille gr, joueur je){
  int i, j;
  char texte[100], score[10];
  MLV_Color color[4] = {MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE};
  
  strcpy(texte, "Joueur 1 \n Score : "); /* on met le score dans un const char */
  sprintf(score,"%d", je.score);
  strcat(texte, score);

  MLV_draw_adapted_text_box(50,390, texte,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER); /* affichage du score du joueur */
  
  for( i = 0 ; i < gr.n ; i++ ){
    for( j = 0; j < gr.m ; j++){
      MLV_draw_filled_rectangle( 200+(j*TCUB), 100+(i*TCUB), TCUB, TCUB, color[gr.mat[i][j]]);
      MLV_draw_rectangle( 200+(j*TCUB), 100+(i*TCUB), TCUB, TCUB, MLV_COLOR_GREY);
    }
  }
}
