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
   
   fichier = fopen("./Saves/score.bin", "wb");
  
   for( i = 0 ; i < 10 ; i++){
   fwrite(&joueurs[i], sizeof(joueur) , 1, fichier);
   }
   fclose(fichier);
   } 
*/

int main(){
  srand(time(NULL));
  MLV_create_window("Puyo","puyo", LX, LY);
  fonctionnement();  
  MLV_free_window();
  exit(EXIT_SUCCESS);
}
