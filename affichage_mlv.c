#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include <string.h>
#define TCUB 50
#define TSUIV 40
#define TVS 40
#define TVSUIV 30


/* charge les images des poyos 1 fois au debut du jeu */
int charger_img(MLV_Image *images[NUM_IMAGES]){
  int i;
  char* noms_images[NUM_IMAGES] = {
    "./assets/poyo_rouge.png",
    "./assets/poyo_vert.png",
    "./assets/poyo_bleu.png",
    "./assets/poyo_jaune.png",
    "./assets/poyo_violet.png"
  };
  for( i = 0 ; i < NUM_IMAGES ; i++){
    images[i] = MLV_load_image(noms_images[i]);
    if( images[i] == NULL ) {
      fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", noms_images[i]);
      return -1;
    }
    MLV_resize_image_with_proportions(images[i], TCUB, TCUB);
  }
  return 1;
}

/* libère les images de poyos a la fin du jeu */
void liberer_images(MLV_Image* images[NUM_IMAGES]){
  int i;
  for( i = 0; i < NUM_IMAGES; i++) {
    if (images[i]) {
      MLV_free_image(images[i]);
    }
  }
}

void aff_etat(grille gr, joueur je, hms chrono, c_poyo poyo, MLV_Image *images[NUM_IMAGES]){
  int i, j;
  char texte[100], score[10], chronometre[20];

  MLV_clear_window(MLV_COLOR_BLACK);
  
  strcpy(texte, "Joueur 1 \n Score : "); /* on met le score dans un const char */
  sprintf(score,"%d", je.score);
  strcat(texte, score);

  
  sprintf(chronometre, "%d:%d:%d:%d", chrono.heures, chrono.minutes, chrono.secondes, chrono.milis);
  MLV_draw_adapted_text_box(600 ,10, chronometre ,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
  
  MLV_draw_adapted_text_box(50,390, texte,10,  MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER); /* affichage du score du joueur */

  for( i = 0 ; i < gr.n ; i++ ){
    for( j = 0; j < gr.m ; j++){
      if( i == 0 && (poyo.p1.x > 0 ) && (poyo.p2.x > 0 ) && (poyo.p1.y == j ||poyo.p2.y == j) ){
	MLV_draw_filled_rectangle( 200+(j*TCUB), 100+(i*TCUB), TCUB, TCUB, MLV_COLOR_DARKRED);
	MLV_draw_rectangle( 200+(j*TCUB), 100+(i*TCUB), TCUB, TCUB, MLV_COLOR_GREY);
      }else{
	MLV_draw_filled_rectangle( 200+(j*TCUB), 100+(i*TCUB), TCUB, TCUB, MLV_COLOR_WHITE);
	if( gr.mat[i][j] > 0 ){
	  MLV_draw_image( images[ gr.mat[i][j] - 1],  200+(j*TCUB), 100+(i*TCUB));
	}
	MLV_draw_rectangle( 200+(j*TCUB), 100+(i*TCUB), TCUB, TCUB, MLV_COLOR_GREY);
      }
    }
  }
}


void aff_poyos(c_poyo *tpoyo, c_poyo *sauvegarde, MLV_Image *images[NUM_IMAGES]){
    int i;

    for(i = 0 ; i < 3 ; i++ ){
      MLV_draw_image( images[ (tpoyo[i + 1].p2.couleur) - 1 ] ,  700, 200+(i*110));
      /* MLV_draw_filled_rectangle(700, 200+(i*90), TSUIV, TSUIV, images[ (tpoyo[i + 1].p2.couleur) - 1 ] ); */
        MLV_draw_rectangle( 700, 200+(i*110), TCUB, TCUB, MLV_COLOR_GREY);

	 MLV_draw_image( images[ (tpoyo[i + 1].p1.couleur) - 1 ] ,  700, 250+(i*110));
	 /* MLV_draw_filled_rectangle(700, 240+(i*90), TSUIV, TSUIV, images ([tpoyo[i + 1].p1.couleur) - 1]); */
	 MLV_draw_rectangle( 700, 250+(i*110), TCUB, TCUB, MLV_COLOR_GREY);
    }

    MLV_draw_text_box( 100, 100, 100, 20, "Sauvegarde", 10, MLV_COLOR_GREY, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_draw_rectangle(100,  120, 100, 120, MLV_COLOR_GREY);

    if( sauvegarde -> p1.couleur > 0 ){
      if( sauvegarde -> p2.couleur != 0 ){
	MLV_draw_image( images[ (sauvegarde -> p2.couleur) - 1 ] , 125, 130);
	/* MLV_draw_filled_rectangle(130,130 , TSUIV, TSUIV, color[sauvegarde -> p2.couleur]); */
        MLV_draw_rectangle( 125, 130, TCUB, TCUB, MLV_COLOR_GREY);
      }

      MLV_draw_image( images[ (sauvegarde -> p1.couleur) - 1 ] , 125, 180);
      /*  MLV_draw_filled_rectangle(130,170 , TSUIV, TSUIV, color[sauvegarde -> p1.couleur]); */
      MLV_draw_rectangle( 125, 180, TCUB, TCUB, MLV_COLOR_GREY);
    }
    
}

/* ------------------------------------------------------ fonctions pour le 1 vs 1 ------------------------------------------------ */

int charger_img_1vs1(MLV_Image *images[NUM_IMAGES_1VS1]){
  int i;
  char* noms_images[NUM_IMAGES_1VS1] = {
    "./assets/poyo_rouge.png",
    "./assets/poyo_vert.png",
    "./assets/poyo_bleu.png",
    "./assets/poyo_jaune.png",
    "./assets/poyo_violet.png",
    "./assets/poyo_noir.png"
  };
  for( i = 0 ; i < NUM_IMAGES_1VS1 ; i++){
    images[i] = MLV_load_image(noms_images[i]);
    if( images[i] == NULL ) {
      fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", noms_images[i]);
      return -1;
    }
    MLV_resize_image_with_proportions(images[i], TVS, TVS);
  }
  return 1;
}


void liberer_images_1vs1(MLV_Image* images[NUM_IMAGES_1VS1]){
  int i;
  for( i = 0; i < NUM_IMAGES_1VS1; i++) {
    if (images[i]) {
      MLV_free_image(images[i]);
    }
  }
}


void aff_1vs1_etat(grille gr1, grille gr2, joueur je1, joueur je2, hms chrono, c_poyo poyo1, c_poyo poyo2, MLV_Image *images[NUM_IMAGES_1VS1]){
  int i, j;
  char texte1[100], texte2[100], score1[10], score2[10], chronometre[20];
  
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
      if( i == 0 && (poyo1.p1.x > 0 ) && (poyo1.p2.x > 0 ) && (poyo1.p1.y == j || poyo1.p2.y == j) ){
	MLV_draw_filled_rectangle( 100+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_DARKRED);
	MLV_draw_rectangle( 100+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_GREY);
      }else	
	MLV_draw_filled_rectangle( 100+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_WHITE);
      if( gr1.mat[i][j] > 0){
	MLV_draw_image( images[ gr1.mat[i][j] - 1],  100+(j*TVS), 100+(i*TVS));
      }
      MLV_draw_rectangle( 100+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_GREY);
    }
  }


for( i = 0 ; i < gr2.n ; i++ ){
  for( j = 0; j < gr2.m ; j++){
    if( i == 0 && (poyo2.p1.x > 0 ) && (poyo2.p2.x > 0 ) && (poyo2.p1.y == j || poyo2.p2.y == j) ){
      MLV_draw_filled_rectangle( 500+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_DARKRED );
      MLV_draw_rectangle( 500+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_GREY);
    }else{
      MLV_draw_filled_rectangle( 500+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_WHITE);
      if( gr2.mat[i][j] > 0){
	MLV_draw_image( images[ gr2.mat[i][j] - 1],  500+(j*TVS), 100+(i*TVS));
      }
      MLV_draw_rectangle( 500+(j*TVS), 100+(i*TVS), TVS, TVS, MLV_COLOR_GREY);
    }
  }
 }
}


void aff_1vs1_poyos(c_poyo *tpoyo1, c_poyo *tpoyo2,  c_poyo *sauvegarde1, c_poyo *sauvegarde2, MLV_Image *images[NUM_IMAGES_1VS1]){
  int i;

  /* ------------------------------------ j1 ---------------------------------------------------- */
  for(i = 0 ; i < 3 ; i++ ){
    MLV_draw_image( images[ (tpoyo1[ i + 1 ].p2.couleur) - 1],  350, 200+(i*110));
    MLV_draw_rectangle( 350, 200+(i*110), TVS, TVS, MLV_COLOR_GREY);

    MLV_draw_image( images[ (tpoyo1[ i + 1 ].p1.couleur) - 1],  350, 240+(i*110)); 
    MLV_draw_rectangle( 350, 240+(i*110), TVS, TVS, MLV_COLOR_GREY);
  }

  MLV_draw_text_box( 0, 100, 100, 20, "Sauvegarde", 10, MLV_COLOR_GREY, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_rectangle(0,  120, 100, 120, MLV_COLOR_GREY);

  if( sauvegarde1 -> p1.couleur > 0 ){
    if( sauvegarde1 -> p2.couleur != 0 ){

      MLV_draw_image( images[ (sauvegarde1 -> p1.couleur) - 1],  30, 140); 
      MLV_draw_rectangle( 30, 140, TVS, TVS, MLV_COLOR_GREY);
    }
    MLV_draw_image( images[ (sauvegarde1 -> p2.couleur) - 1],  30, 180); 
    MLV_draw_rectangle( 30, 180, TVS, TVS, MLV_COLOR_GREY);
  }

  /* ----------------------------------- j2 --------------------------------------------------- */

  for(i = 0 ; i < 3 ; i++ ){
    MLV_draw_image( images[ (tpoyo2[ i + 1 ].p2.couleur) - 1],  750, 200+(i*110));
    MLV_draw_rectangle( 750, 200+(i*110), TVS, TVS, MLV_COLOR_GREY);

    MLV_draw_image( images[ (tpoyo2[ i + 1 ].p1.couleur) - 1],  750, 240+(i*110)); 
    MLV_draw_rectangle( 750, 240+(i*110), TVS, TVS, MLV_COLOR_GREY);
  }

  MLV_draw_text_box( 400, 100, 100, 20, "Sauvegarde", 10, MLV_COLOR_GREY, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
  MLV_draw_rectangle(400,  120, 100, 120, MLV_COLOR_GREY);

  if( sauvegarde2 -> p1.couleur > 0 ){
    if( sauvegarde2 -> p2.couleur != 0 ){
      MLV_draw_image( images[ (sauvegarde2 -> p1.couleur) - 1],  430, 140); 
      MLV_draw_rectangle( 430, 140, TVS, TVS, MLV_COLOR_GREY);
    }
    MLV_draw_image( images[ (sauvegarde2 -> p2.couleur) - 1],  430, 180); 
    MLV_draw_rectangle( 430, 180, TVS, TVS, MLV_COLOR_GREY);
  }
   
}
