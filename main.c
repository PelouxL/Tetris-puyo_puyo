#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "grille.h"
#include "pieces.h"
#include "affichage_mlv.h"

int main(){
  int n = 10, m = 8, test, bol=1;
  grille gr;
  joueur j;
  c_poyo c1;

  
  srand(time(NULL));
  MLV_create_window("Puyo","puyo", LX, LY);
   
  j.pseudo = "Moi";
  j.score = 1500;


  
  aff_jeu();
  gr= initialisation_grille(n,m);

  initialisation_cpoyo(&c1);
  apparition_piece(&c1, &gr);

  while( bol == 1){


    test = est_dessous(c1.p1, gr);
    printf("%d\n",test);
  

    aff_grille(gr);
    aff_etat(gr, j);
    
    MLV_wait_seconds(2);
    avancement_piece(&c1, &gr);
    MLV_actualise_window();
  }
  MLV_wait_seconds(7);
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
