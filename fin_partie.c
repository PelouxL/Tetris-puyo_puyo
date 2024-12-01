#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "score.h"

int verif_fin( c_poyo poyo, grille gr ){
  /* on verifie si un poyo a ete poser a l'endroit de l'initialisation */
  if( (poyo.p1.pos == 1 && ( poyo.p1.x == 0 && poyo.p1.y == gr.m/2 ) ) ||
      ( (poyo.p2.pos == 1 && ( poyo.p2.x == 0 && poyo.p2.y == gr.m/2 )))){
    return 1;
  }
  return 0;
}
/* permet de finir une partie et de mettre a jour le tableau score */

int fin_solo( c_poyo poyo, joueur je, grille gr ){
  tjoueur tmp_tjoueur;
  if( (verif_fin( poyo, gr) ) == 1 ){

    printf(" rentrer un pseudo \n");

    if( recup_score("score.txt", &tmp_tjoueur) == -1 ){
      fprintf( stderr, "Erreur lors de la recupperation du score\n");
      return -1;
    }

    if( (tri_insertion( "score.txt", je, &tmp_tjoueur) ) == -1){
      fprintf( stderr, "Erreur lors de l'actualisation du score\n");
      return -1;
    }
  }
  return 1;
}
      

int fin_1vs1( c_poyo poyo1, c_poyo poyo2, joueur je1, joueur je2, grille gr1, grille gr2){
  tjoueur tmp_tjoueur;
  if( (verif_fin( poyo1, gr1 ) == 1) || (verif_fin( poyo2, gr2 ) == 1) ){
    
    if( (verif_fin( poyo1, gr1 ) == 1) ){
      printf("bravo J2\n");
    }else{
      printf("bravo j1\n");
    }
  }
  return 1;
}
