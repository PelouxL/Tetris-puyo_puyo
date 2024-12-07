#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>
#include "ini_poyo.h"
#define TCUB 50
#define TSUIV 40
#define TVS 40
#define TVSUIV 30

void aff_etat(grille gr, joueur je, hms chrono){
  int i, j;
  char texte[100], score[10], chronometre[20];
  MLV_Color color[7] = {MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE, MLV_COLOR_YELLOW, MLV_COLOR_PURPLE, MLV_COLOR_GREY};

   MLV_clear_window(MLV_COLOR_BLACK);
  strcpy(texte, "Joueur 1 \n Score : "); /* on met le score dans un const char */
  sprintf(score,"%d", je.score);
  strcat(texte, score);
  
  sprintf(chronometre, "%d:%d:%d:%d", chrono.heures, chrono.minutes, chrono.secondes, chrono.milis);
  MLV_draw_adapted_text_box(600 ,10, chronometre ,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
  
  MLV_draw_adapted_text_box(50,390, texte,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER); /* affichage du score du joueur */
  
  for( i = 0 ; i < gr.n ; i++ ){
    for( j = 0; j < gr.m ; j++){
      MLV_draw_filled_rectangle( 200+(j*TCUB), 100+(i*TCUB), TCUB, TCUB, color[gr.mat[i][j]]);
      MLV_draw_rectangle( 200+(j*TCUB), 100+(i*TCUB), TCUB, TCUB, MLV_COLOR_GREY);
    }
  }
}

void aff_poyos(tc_poyo *tpoyo, c_poyo *sauvegarde){
  MLV_Color color[6] = {MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE,  MLV_COLOR_YELLOW, MLV_COLOR_PURPLE};
    int i;

    for(i = 0 ; i < 3 ; i++ ){
       affiche_c_poyo(tpoyo[i+1]);
        MLV_draw_filled_rectangle(700, 200+(i*90), TSUIV, TSUIV, color[tpoyo[i + 1] -> p2.couleur]);
        MLV_draw_rectangle( 700, 200+(i*90), TSUIV, TSUIV, MLV_COLOR_GREY);
        
        MLV_draw_filled_rectangle(700, 240+(i*90), TSUIV, TSUIV, color[tpoyo[i + 1] -> p1.couleur]);
        MLV_draw_rectangle( 700, 240+(i*90), TSUIV, TSUIV, MLV_COLOR_GREY);
    }
    
    MLV_draw_text_box( 100, 100, 100, 20, "Sauvegarde", 10, MLV_COLOR_GREY, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_rectangle(100,  120, 100, 100, MLV_COLOR_GREY);

    if( sauvegarde -> p1.couleur > 0 ){
        if( sauvegarde -> p2.couleur != 0 ){
        MLV_draw_filled_rectangle(130,130 , TSUIV, TSUIV, color[sauvegarde -> p2.couleur]);
        MLV_draw_rectangle( 130, 130, TSUIV, TSUIV, MLV_COLOR_GREY);
        }
        
        MLV_draw_filled_rectangle(130,170 , TSUIV, TSUIV, color[sauvegarde -> p1.couleur]);
        MLV_draw_rectangle( 130, 170, TSUIV, TSUIV, MLV_COLOR_GREY);
    }
    
}

/* ------------------------------------------------------ fonctions pour le 1 vs 1 ------------------------------------------------ */

void aff_1vs1_etat(grille gr1, grille gr2, joueur je1, joueur je2, hms chrono){
  int i, j;
  char texte1[100], texte2[100], score1[10], score2[10], chronometre[20];
  MLV_Color color[7] = {MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE, MLV_COLOR_YELLOW, MLV_COLOR_PURPLE, MLV_COLOR_BLACK};

  MLV_clear_window(MLV_COLOR_BLACK);

  /* gestion du nom et du score du j1 */
  strcpy(texte1, "Joueur 1 \n Score : "); /* on met le score dans un const char */
  sprintf(score1,"%d", je1.score);
  strcat(texte1, score1);

  /* puis celui du j2 */
  strcpy(texte2, "Joueur 2 \n Score : "); 
  sprintf(score2,"%d", je2.score);
  strcat(texte2, score2);

  sprintf(chronometre, "%d:%d:%d:%d", chrono.heures, chrono.minutes, chrono.secondes, chrono.milis);
  MLV_draw_adapted_text_box(400 ,10, chronometre ,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
  
  MLV_draw_adapted_text_box(180,600, texte1,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER); /* affichage du score du joueur 1 */
  MLV_draw_adapted_text_box(580,600, texte2,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER); /* affichage du score du joueur 2 */
  
  for( i = 0 ; i < gr1.n ; i++ ){
    for( j = 0; j < gr1.m ; j++){
      MLV_draw_filled_rectangle( 100+(j*TVS), 100+(i*TVS), TVS, TVS, color[gr1.mat[i][j]]);
      MLV_draw_rectangle( 100+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_GREY);
    }
  }

  for( i = 0 ; i < gr2.n ; i++ ){
    for( j = 0; j < gr2.m ; j++){
      MLV_draw_filled_rectangle( 500+(j*TVS), 100+(i*TVS), TVS, TVS, color[gr2.mat[i][j]]);
      MLV_draw_rectangle( 500+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_GREY);
    }
  }
}


void aff_1vs1_poyos(tc_poyo *tpoyo1, tc_poyo *tpoyo2,  c_poyo *sauvegarde1, c_poyo *sauvegarde2){
  MLV_Color color[6] = {MLV_COLOR_WHITE, MLV_COLOR_RED, MLV_COLOR_GREEN, MLV_COLOR_BLUE,  MLV_COLOR_YELLOW, MLV_COLOR_PURPLE};
    int i;

    /* ------------------------------------ j1 ---------------------------------------------------- */
    for(i = 0 ; i < 3 ; i++ ){
        MLV_draw_filled_rectangle(350, 200+(i*70), TVSUIV, TVSUIV, color[tpoyo1[i + 1] -> p2.couleur]);
        MLV_draw_rectangle( 350, 200+(i*70), TVSUIV, TVSUIV, MLV_COLOR_GREY);
        
        MLV_draw_filled_rectangle(350, 230+(i*70), TVSUIV, TVSUIV, color[tpoyo1[i + 1] -> p1.couleur]);
        MLV_draw_rectangle( 350, 230+(i*70), TVSUIV, TVSUIV, MLV_COLOR_GREY);
    }

    MLV_draw_text_box( 0, 100, 100, 20, "Sauvegarde", 10, MLV_COLOR_GREY, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_rectangle(0,  120, 100, 100, MLV_COLOR_GREY);

    if( sauvegarde1 -> p1.couleur > 0 ){
        if( sauvegarde1 -> p2.couleur != 0 ){
        MLV_draw_filled_rectangle(30,140 , TVSUIV, TVSUIV, color[sauvegarde1 -> p2.couleur]);
        MLV_draw_rectangle( 30, 140, TVSUIV, TVSUIV, MLV_COLOR_GREY);
        }
        
        MLV_draw_filled_rectangle(30,170 , TVSUIV, TVSUIV, color[sauvegarde1 -> p1.couleur]);
        MLV_draw_rectangle( 30, 170, TVSUIV, TVSUIV, MLV_COLOR_GREY);
    }

    /* ----------------------------------- j2 --------------------------------------------------- */

    for(i = 0 ; i < 3 ; i++ ){
      MLV_draw_filled_rectangle(750, 200+(i*70), TVSUIV, TVSUIV, color[tpoyo2[i + 1] -> p2.couleur]);
      MLV_draw_rectangle( 750, 200+(i*70), TVSUIV, TVSUIV, MLV_COLOR_GREY);
        
      MLV_draw_filled_rectangle(750, 230+(i*70), TVSUIV, TVSUIV, color[tpoyo2[i + 1] -> p1.couleur]);
      MLV_draw_rectangle( 750, 230+(i*70), TVSUIV, TVSUIV, MLV_COLOR_GREY);
    }

    MLV_draw_text_box( 400, 100, 100, 20, "Sauvegarde", 10, MLV_COLOR_GREY, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_rectangle(400,  120, 100, 100, MLV_COLOR_GREY);

    if( sauvegarde2 -> p1.couleur > 0 ){
      if( sauvegarde2 -> p2.couleur != 0 ){
        MLV_draw_filled_rectangle(430,130 , TSUIV, TSUIV, color[sauvegarde2 -> p2.couleur]);
        MLV_draw_rectangle( 430, 130, TSUIV, TSUIV, MLV_COLOR_GREY);
      }
        
      MLV_draw_filled_rectangle(430,160 , TSUIV, TSUIV, color[sauvegarde2 -> p1.couleur]);
      MLV_draw_rectangle( 430, 160, TSUIV, TSUIV, MLV_COLOR_GREY);
    }
   
}
