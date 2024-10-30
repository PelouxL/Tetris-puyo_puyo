#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "grille.h"

int main(){
  int n = 10, m = 5;
  grille gr;
  
  gr= initialisation_grille(n,m);
  aff_grille(gr);
  exit(EXIT_SUCCESS);
}
