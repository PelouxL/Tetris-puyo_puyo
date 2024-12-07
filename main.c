#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "grille.h"
#include "pieces.h"
#include "ini_poyo.h"
#include "jeu.h"
#include "affichage_mlv.h"
#include "destruction.h"
#include "menu.h"

int main(){
    int n = 12, m = 6; 
   grille gr1, gr2; 
   joueur je1, je2; 
   c_poyo tpoyo1[4], tpoyo2[4];  

  srand(time(NULL));
  MLV_create_window("Puyo","puyo", LX, LY);

     je1.score = 0; 
  je2.score = 1500; 

   gr1 = initialisation_grille(n,m); 
   gr2 = initialisation_grille(n,m); 

   ini_poyo_chaine(tpoyo1, 4);
   ini_poyo_chaine(tpoyo2, 4); 

   /* fonctionnement(); */
  /* jeu(&gr1, &je1, tpoyo1); */
    jeu_1vs1(&gr1, &gr2, &je1, &je2, tpoyo1, tpoyo2);
  
  MLV_wait_seconds(7);
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
