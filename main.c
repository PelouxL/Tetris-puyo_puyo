#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "grille.h"
#include "pieces.h"
#include "ini_poyo.h"
#include "affichage_mlv.h"

int main(){
  int n = 10, m = 8, tmp_prc, tmp_act, ok = 0;
  grille gr;
  joueur j;
  c_poyo tpoyo[4];

  
  srand(time(NULL));
  MLV_create_window("Puyo","puyo", LX, LY);
   
  j.pseudo = "Moi";
  j.score = 1500;

  
  aff_jeu();
  gr= initialisation_grille(n,m);

  ini_poyo_chaine(tpoyo, 4);
  tmp_prc = MLV_get_time();
  
  while(1){
    tmp_act = MLV_get_time();
    roulement_poyo(tpoyo, &gr, 4);
    if( tmp_act - tmp_prc >= 1000){
      avancement_piece(&tpoyo[0], &gr);
      tmp_prc = tmp_act ;
    }

    
    aff_grille(gr);
    aff_etat(gr, j);
    
    printf("\n");

    deplacement(&tpoyo[0], &gr);
    
    affiche_c_poyo(&tpoyo[0]);
    actualisation_poyo(&tpoyo[0], &gr);

    if(tpoyo[0].p1.pos == 1 && tpoyo[0].p2.pos == 1){
      ok++;
    }
    MLV_actualise_window();
  }
  MLV_wait_seconds(7);
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
