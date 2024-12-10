#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "score.h"
#include "destruction.h"

int verif_fin( c_poyo poyo, grille gr ){
  int j;
  /* on verifie si un poyo a ete poser a l'endroit de l'initialisation */
  for( j = 0 ; j < gr.m ; j++ ){
    if(gr.mat[0][j] != 0 && (poyo.p1.pos == 1 && poyo.p2.pos == 1)){
      return 1;
    }
  }
  
  return 0;
}
/* permet de finir une partie et de mettre a jour le tableau score */

int fin_solo( c_poyo poyo, joueur je, grille gr, int dest ){
  tjoueur tmp_tjoueur;
  char *pseudo = NULL;
  
  if( verif_fin( poyo, gr) == 1 && dest == 0){
    MLV_clear_window(MLV_COLOR_BEIGE);

    /* boite pour ecrire le pseudo */
    MLV_wait_input_box( 100, 100, 300, 50,  MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_COLOR_WHITE, "Entrez votre pseudo : ", &pseudo );
    
    /* on verifie si il y a une erreur */
    if (pseudo == NULL) {
      fprintf(stderr, "Erreur : Aucun pseudo saisi.\n");
      return -1;
    }

    strncpy(je.pseudo, pseudo, sizeof(je.pseudo) - 1);
    je.pseudo[sizeof(je.pseudo) - 1] = '\0'; 

    free(pseudo );

    if( recup_score("./Saves/score.bin", tmp_tjoueur) == -1 ){
      fprintf( stderr, "Erreur lors de la recupperation du score\n");
      return -1;
    }
    
    if( (tri_insertion( "./Saves/score.bin", je, tmp_tjoueur) ) == -1){
      fprintf( stderr, "Erreur lors de l'actualisation du score\n");
      return -1;
    }
    /* partie fini et aucun problème */
    return 1;
  }
  /* la fonction est appeler mais partie n'est pas fini */
  return 0; 
}
      

int fin_1vs1( c_poyo poyo1, c_poyo poyo2, joueur je1, joueur je2, grille gr1, grille gr2, int dest1, int dest2){
  char text[50], score[10];

  /* on verifie si quelqu'un a perdu */
  if( (verif_fin( poyo1, gr1 ) == 1 && dest1 == 0) || (verif_fin( poyo2, gr2 ) == 1 && dest2 == 0) ){
    MLV_clear_window(MLV_COLOR_BEIGE);

    /* on verifie si c'est j1 ou j2 qui a perdu */
    if( verif_fin( poyo1, gr1 ) == 1){
      
      strcpy(text, "Bravo Joueur 2 tu as gagné avec : ");
      sprintf(score, "%d !\n", je2.score);
      strcat(text, score);
      printf("bravo J2\n");
      
    }else{
      strcpy(text, "Bravo Joueur 1 tu as gagné avec : ");
      sprintf(score, "%d !\n", je1.score);
      strcat(text, score);
      
      printf("bravo j1\n");
    }
    
    MLV_draw_adapted_text_box( 400, 300, text, 10, MLV_ALPHA_TRANSPARENT, MLV_COLOR_RED, MLV_ALPHA_TRANSPARENT, MLV_TEXT_CENTER);
    MLV_actualise_window();
    MLV_wait_seconds(2);

    return 1;
  }
  /* la partie n'est pas fini */
  return 0;
}
