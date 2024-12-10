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

/* 
void ec(){
  int i;
  FILE *fichier;
   tjoueur joueurs = {
        {"Pl1", 1000},
        {"Pl2", 950},
        {"Pl3", 900},
        {"Pl4", 850},
        {"Pl5", 800},
        {"Pl6", 750},
        {"Pl7", 700},
        {"Pl8", 650},
        {"Pl9", 600},
        {"Pl10", 550}
    };
   
  fichier = fopen("score.bin", "wb");
  
  for( i = 0 ; i < 10 ; i++){
    fwrite(&joueurs[i], sizeof(joueur) , 1, fichier);
  }
  fclose(fichier);
  } 
*/

int main(){
  /* int n = 12, m = 6; 
   grille gr1, gr2; 
   joueur je1, je2; 
   c_poyo tpoyo1[4], tpoyo2[4];  
  */
  srand(time(NULL));
  MLV_create_window("Puyo","puyo", LX, LY);
  
  /*
  je1.score = 0; 
  je2.score = 1500; 

   gr1 = initialisation_grille(n,m); 
   gr2 = initialisation_grille(n,m); 

   ini_poyo_chaine(tpoyo1, 4);
   ini_poyo_chaine(tpoyo2, 4);  */

  fonctionnement();  
   /* jeu_1vs1(&gr1, &gr2, &je1, &je2, tpoyo1, tpoyo2); */
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
