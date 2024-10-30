#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>

void aff_jeu(){
  MLV_clear_window(MLV_COLOR_YELLOW3);
  MLV_draw_filled_rectangle(200, 100, 400, 600, MLV_COLOR_WHITE);
}

void aff_etat(grille gr, joueur je){
  int i, j;
  char texte[100], score[10];

  strcpy(texte, "Joueur 1 \n Score : "); /* on met le score dans un const char */
  sprintf(score,"%d", je.score);
  strcat(texte, score);

  MLV_draw_adapted_text_box(50,390, texte,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER); /* affichage du score du joueur */
  
  for( i = 0 ; i < gr.n ; i++ ){
    for( j = 0; j < gr.m ; j++){
      switch (gr.mat[i][j]){ /* Choix des couleur en fonction de la valeur de mat[i][j] */
      case 1:
	 MLV_draw_filled_rectangle( 200+(j*60), 100+(i*60), 60, 60, MLV_COLOR_RED);
	 break;
      case 2:
	MLV_draw_filled_rectangle( 200+(j*60), 100+(i*60), 60, 60, MLV_COLOR_GREEN);
	break;
      case 3:
       	MLV_draw_filled_rectangle( 200+(j*60), 100+(i*60), 60, 60, MLV_COLOR_BLUE);
	break;
      default:
	MLV_draw_filled_rectangle( 200+(j*60), 100+(i*60), 60, 60, MLV_COLOR_WHITE);
	break;
      }
      MLV_draw_rectangle( 200+(j*60), 100+(i*60), 60, 60, MLV_COLOR_GREY);
    }
  }
}
