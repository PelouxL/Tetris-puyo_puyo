#include <stdlib.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
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
  char *pseudo = NULL;
  
  if( (verif_fin( poyo, gr) ) == 1 ){
    MLV_clear_window(MLV_COLOR_BLACK);

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

    
    if( recup_score("score.bin", &tmp_tjoueur) == -1 ){
      fprintf( stderr, "Erreur lors de la recupperation du score\n");
      return -1;
    }
    
    if( (tri_insertion( "score.bin", je, &tmp_tjoueur) ) == -1){
      fprintf( stderr, "Erreur lors de l'actualisation du score\n");
      return -1;
    }
    /* partie fini et aucun problème */
    return 1;
  }
  /* la fonction est appeler mais partie n'est pas fini */
  return 0; 
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
