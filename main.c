#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "grille.h"
#include "pieces.h"
#include "affichage_mlv.h"

int main(){
  int n = 10, m = 8, tmp_prc, tmp_act, ok = 0;
  grille gr;
  joueur j;
  c_poyo tpoyo[3];
 

  
  srand(time(NULL));
  MLV_create_window("Puyo","puyo", LX, LY);
   
  j.pseudo = "Moi";
  j.score = 1500;


  
  aff_jeu();
  gr= initialisation_grille(n,m);

  ini_poyo_chaine(tpoyo, 3);
  
  tmp_prc = MLV_get_time();
  
  while(ok < 3){
    tmp_act = MLV_get_time();
    if( tpoyo[ok].apparait == 0 ){
      apparition_piece(&tpoyo[ok], &gr);
      tpoyo[ok].apparait = 1;
    }
    if( tmp_act - tmp_prc >= 1000){
      avancement_piece(&tpoyo[ok], &gr);
      tmp_prc = tmp_act ;
    
    }

    
    aff_grille(gr);
    aff_etat(gr, j);
    
    printf("%d\n",ok);
    deplacement(&tpoyo[ok], &gr);
    affiche_c_poyo(&tpoyo[ok]);
    actualisation_poyo(&tpoyo[ok], &gr);

    if(tpoyo[ok].p1.pos == 1 && tpoyo[ok].p2.pos == 1){
      ok++;
    }
    MLV_actualise_window();
  }
  MLV_wait_seconds(7);
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
