#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "grille.h"
#include "pieces.h"
#include "affichage_mlv.h"

int main(){
  int n = 10, m = 8;
  grille gr;
  joueur j;
  j.pseudo = "Moi";
  j.score = 1500;

  
  srand(time(NULL));
  MLV_create_window("Puyo","puyo", LX, LY);
  
  aff_jeu();
  gr= initialisation_grille(n,m);
  aff_grille(gr);
  aff_etat(gr, j);
  MLV_actualise_window();
  MLV_wait_seconds(7);
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
