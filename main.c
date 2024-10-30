#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "types.h"
#include "grille.h"

int main(){
  int n = 10, m = 5;
  grille gr;
  srand(time(NULL));

  
  gr= initialisation_grille(n,m);
  aff_grille(gr);
  exit(EXIT_SUCCESS);
}
