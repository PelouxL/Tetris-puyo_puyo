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

int main(){
  int n = 10, m = 8;
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

  jeu(&gr, &j, tpoyo);
  
  MLV_wait_seconds(7);
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
