#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>
#define TCUB 50
#define TSUIV 40

void aff_jeu(){
  MLV_clear_window(MLV_COLOR_BLACK);
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

void aff_poyos(c_poyo *tpoyo, c_poyo *sauvegarde){
    MLV_Color color[4] = {MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE};
    int i;

    for(i = 0 ; i < 3 ; i++ ){
        MLV_draw_filled_rectangle(700, 200+(i*90), TSUIV, TSUIV, color[tpoyo[i + 1].p2.couleur]);
        MLV_draw_rectangle( 700, 200+(i*90), TSUIV, TSUIV, MLV_COLOR_GREY);
        
        MLV_draw_filled_rectangle(700, 240+(i*90), TSUIV, TSUIV, color[tpoyo[i + 1].p1.couleur]);
        MLV_draw_rectangle( 700, 240+(i*90), TSUIV, TSUIV, MLV_COLOR_GREY);
    }

    MLV_draw_text_box( 100, 100, 100, 20, "Sauvegarde", 10, MLV_COLOR_GREY, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_rectangle(100,  120, 100, 100, MLV_COLOR_GREY);

    if( sauvegarde -> p1.couleur > 0 ){
        MLV_draw_filled_rectangle(130,130 , TSUIV, TSUIV, color[sauvegarde -> p2.couleur]);
        MLV_draw_rectangle( 130, 130, TSUIV, TSUIV, MLV_COLOR_GREY);

        MLV_draw_filled_rectangle(130,170 , TSUIV, TSUIV, color[sauvegarde -> p1.couleur]);
        MLV_draw_rectangle( 130, 170, TSUIV, TSUIV, MLV_COLOR_GREY);
    }
    
}